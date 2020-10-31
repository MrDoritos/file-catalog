# file-catalog library version 2

### Changes

#### Scope

The file-catalog library will now have a restricted scope directed towards tags, files, and archives (last referred to as discs)

This change in scope was caused by an unclear scope set by myself. The scope of this library should be very narrow. Anything that adds onto this library has different intentions and will need things that this library should not provide. Such as a GUI, modules that search for signatures, file system scrapers, etc.

Because of this new restricted scope, I expect less work to be done towards this library itself.

On the other hand, I will provide a framework for anyone who decides to use the library. Such as a serializer/deserializer (for elements defined by my library only; aka flatfile).

#### Refactoring

* Discs are now referred to as archives. Originally, this library was going to be used to catalog (index) files on discs. The name actually stuck, and I was about to refer to just about everything as a disc, now it's a tad bit more clear.

* jaggedbitarray and intobjectarray will now be referred to as their full name.

* handler is now objectHandler, to make it's purpose clear

* I did some reorganizing of data structure classes so that they are actually readable. I wrote the C++ version of this library (I've written this same library a few times for some reason) in nano, before I learned about the -i flag. Not only were there no tabs in the original code, I didn't know anything about good looking C++.

* Declaration and implementation (header and source) files are now kept seperate. This improves build time and makes cross reference bugs easier to kill. Template classes are still one file, obviously.

#### Other

* Project will use cmake in the future. No more .sh and .bat build scripts. You're welcome. Currently lack any way to build because the library is still being rewritten and there is nothing to build.
