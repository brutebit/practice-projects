use std::{io, string::FromUtf8Error};

#[derive(thiserror::Error, Debug)]
pub enum Error {
    #[error(transparent)]
    IoError(#[from] io::Error),

    #[error(transparent)]
    GitError(#[from] git2::Error),

    #[error(transparent)]
    FromUtf8Error(#[from] FromUtf8Error),

    #[error("Unknown action '{0}'")]
    UnknownAction(char),
}
