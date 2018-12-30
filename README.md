# file-catalog
A file catalogging library in C++

## What is this
A tool to help find, store, and manage files. Its primary purpose is to catalog, 
but many other features (that have already been designed), are planned to be
developed soon.

HOWEVER, it is not yet a tool. It will be a library for the time being.

## How to build
All headers go in the same folder or alternatively use -I to include the
directory. Make sure to do --recursive when you do a clone, as I use my
custom [Moorepp](http://localhost/) framework.
You could also try my [build file](https://github.com/MrDoritos/file-catalog/blob/master/build.sh) for g++.

## What makes a proper tag?
Nouns.

Refrain from phrases, hypens, quotation marks, disambiguity, plurals,
__articles__, uppercase (though should be automatically lowered in software),
and prepositions.

| Bad tag       | Good tag      |
|---------------|---------------|
| `a tree`      | `tree`        |
| `LOWERCASE`   | `lowercase`   |

Since we are working with streams of bytes (hence revolving around hashes),
mime types must be included.

A photo, for example<br />
`800x600`<br />
`12 megapixel`<br />
`no flash`<br />
Might have a standard for representing color<br />
`32 bit`<br />
`rgba`<br />
Use mime, no file extensions<br />
`image/jpeg`

`eiffel tower`<br />
`nighttime`<br />
`midnight`<br />
`2018-12-31T23:59:99-99:99` ISO 8601<br />
`paris`<br />
`france`<br />
Bit extreme<br />
`europe`<br />
`earth`<br />
`48.8584° N, 2.2945° E`
