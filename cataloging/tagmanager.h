#include "tag.h"
#include "jba.h"
#pragma once

class tagmanager {
public:
tagmanager() {
tags = jaggedbitarray();
}
tag* addtag(tag& tag) {
tags.add(tag.id);
return &tag;
}
bool tagexists(int i) {
return tags.exists(i);
}
void removetag(int i) {
tags.remove(i);
}
private:
jaggedbitarray tags;
};
