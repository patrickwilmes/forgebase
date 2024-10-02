create table IF NOT EXISTS files (
    path TEXT PRIMARY KEY,
    type INTEGER NOT NULL,
    name TEXT NOT NULL
);