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
`megapixels: 12`<br />
`flash: off`<br />
Might have a standard for representing color<br />
`bits per pixel: 32`<br />
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

# This documentation is a bit wank, good thing nobody ever sees this
## The standard?
Mime. <br />
Absolutely neccessary, every submission needs one <br />
If in doubt, `application/octet-stream` (DON'T!!) <br />
If there is not a mime for that file, we can define our own <br />

### Representing images
#### Color & Depth
Hopefully your images aren't encoded funny..<br />
`bits per pixel: (bits)` Bits per Pixel <br />
`color mode: (r)(g)(b)(a)` Red Green Blue Alpha. Seriously if you have to remove $
`(width)x(height)` Width times height, seems pretty simple <br />
#### Photo info
If a camera took it, you gotta include these (most of the time) <br />
`flash: (on/off)` <br />
~~`shutter time: (ISO 8601 time format)`~~ JK <br />
`shutter time: (in fractions)` (1/8000, 1/874, 1) <br />
`technology: (image technology)` <br />
#### Image info
`time taken: (ISO 8601 time format)` <br />
`model: (camera model)` <br />
`manufacturer: (camera manufacturer)` <br />
`gps altitude: (in meters)` <br />
`gps latitude: (honestly idk how to represent this so whatever feels great)` <br $
`gps longitude: (same thing as above i assume)` <br />
#### Media info
`lossless: (true/false)` <br />
`raw: (true/false)` <br />
`compression method: (none/jpeg/png)` I don't know if I have my facts straight <b$
`encoding: (png/bitmap/jpeg)` <br />
### Representing audio
#### I'm tired of typing the html break
`bitrate: (bits per second)` <br />
`lossless: (true/false)` <br />
`container: (mp3, flac, aac, midi)` <br />
#### Alright I'm done typing, I'm doing something else


