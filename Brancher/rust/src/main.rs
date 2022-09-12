use branch::{BranchAction, BranchInfo};
use crossterm::terminal;
use error::Error;
use git2::Repository;
use std::{
    convert::TryFrom,
    io::{self, Bytes, Read, Stdin, Stdout, Write},
};

mod branch;
mod error;

type Result<T, E = Error> = std::result::Result<T, E>;

fn main() -> Result<()> {
    terminal::enable_raw_mode()?;
    let result = start();
    terminal::disable_raw_mode()?;
    result
}

fn start() -> Result<()> {
    let repo = Repository::open_from_env()?;
    let branches = BranchInfo::extract(&repo)?;
    let mut stdout = io::stdout();
    let mut stdin = io::stdin().bytes();

    'outer: for mut branch in branches {
        if branch.is_head {
            write!(stdout, "Ignoring {} cause it is head...\n\r", branch.name)?;
            stdout.flush()?;
            continue;
        }
        loop {
            let action = get_branch_action(&branch, &mut stdout, &mut stdin);
            match action {
                Err(error) => match error {
                    Error::UnknownAction(_) => {
                        let mut stderr = io::stderr();
                        write!(stderr, "\n\r{}\n\r", error)?;
                        stderr.flush()?;
                        continue;
                    }
                    other => {
                        return Err(other);
                    }
                },
                Ok(action) => match action {
                    BranchAction::Quit => {
                        write!(stdout, "\n\rhave a good day\n\r")?;
                        stdout.flush()?;
                        break 'outer;
                    }
                    BranchAction::Keep => {
                        write!(stdout, "\n\rkeep\n\r")?;
                        stdout.flush()?;
                        break;
                    }
                    BranchAction::Delete => {
                        stdout.flush()?;
                        branch.delete()?;
                        write!(
                            stdout,
                            "\n\rdeleted.. to undo run git branch {} {}\n\r",
                            branch.name, branch.id
                        )?;
                        break;
                    }
                    BranchAction::Help => {
                        write!(stdout, "\n\rk: Keep, d: Delete, q: Quit, ?: Help\n\r")?;
                        stdout.flush()?;
                        continue;
                    }
                },
            }
        }
    }
    write!(stdout, "No more branches...\n\r")?;
    stdout.flush()?;
    Ok(())
}

fn get_branch_action(
    branch: &BranchInfo,
    stdout: &mut Stdout,
    stdin: &mut Bytes<Stdin>,
) -> Result<BranchAction> {
    write!(
        stdout,
        "'{}' ({}) last commit at {} (k/d/q/?) > ",
        branch.name,
        &branch.id.to_string()[..10],
        branch.time
    )?;
    stdout.flush()?;

    let byte = match stdin.next() {
        Some(byte) => byte?,
        None => return get_branch_action(branch, stdout, stdin),
    };

    let c = char::from(byte);
    write!(stdout, "{}", c)?;
    stdout.flush()?;

    Ok(BranchAction::try_from(c)?)
}
