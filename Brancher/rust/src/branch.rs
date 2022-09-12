use chrono::{Duration, NaiveDateTime};
use git2::{Branch, BranchType, Oid, Repository};

use crate::{error::Error, Result};

pub struct BranchInfo<'repo> {
    pub id: Oid,
    pub name: String,
    pub time: NaiveDateTime,
    pub branch: Branch<'repo>,
    pub is_head: bool,
}
impl<'repo> BranchInfo<'repo> {
    pub fn delete(&mut self) -> Result<()> {
        self.branch.delete().map_err(From::from)
    }

    pub fn extract(repo: &Repository) -> Result<Vec<BranchInfo>> {
        let mut branches = repo
            .branches(Some(BranchType::Local))?
            .map(|branch| {
                let (branch, _) = branch?;
                let name = String::from_utf8((branch.name_bytes()?).to_vec())?;
                let commit = branch.get().peel_to_commit()?;
                let id = commit.id();
                let time = commit.time();
                let offset = Duration::minutes(time.offset_minutes() as i64);
                let time = NaiveDateTime::from_timestamp(time.seconds(), 0) + offset;

                Ok(BranchInfo {
                    id,
                    name,
                    time,
                    is_head: branch.is_head(),
                    branch,
                })
            })
            .collect::<Result<Vec<_>>>()?;

        branches.sort_by_key(|branch| branch.time);
        Ok(branches)
    }
}

pub enum BranchAction {
    Keep,
    Quit,
    Delete,
    Help,
}
impl TryFrom<char> for BranchAction {
    type Error = Error;

    fn try_from(value: char) -> Result<Self, Self::Error> {
        match value {
            'd' => Ok(Self::Delete),
            'k' => Ok(Self::Keep),
            '?' => Ok(Self::Help),
            'q' => Ok(Self::Quit),
            other => Err(Self::Error::UnknownAction(other)),
        }
    }
}
