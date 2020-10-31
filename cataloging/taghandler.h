#pragma once
#include "ioa.h"
#include "tag.h"
#include "idmanager.h"
#include <string.h>

class taghandler {
public:
taghandler() {
tags = intobjectarray(16);
tagids = idmanager();
}
tag* addtag(tag* tag) {
tag.id = tagids.peekId();
tags.add(tag, tagids.newId());
return tag;
}
tag* addtag(std::string* text) {
tag* ntag = new tag(text, tagids.peekId());
tags.add(ntag, tagids.newId());
return ntag;
}
tag* addtag(std::string* text, int id) {
tag* ntag = new tag(text, tagids.peekId());
tags.add(ntag, tagids.newId());
return ntag;
}
tag* gettag(int id) {

}
private:
//Underlying array of tags
intobjectarray<tag> tags;
//Tag Ids
idmanager tagids;
};
