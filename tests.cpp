#include <iostream>
#include "console.h"
#include "idmanager.h"
#include "file.h"
#include "tag.h"
#include "tagmanager.h"
#include "bitarray.h"
#include "jba.h"
#include "sha.h"
#include "cindex.h"
#include "database.h"
#include "tcpclient.h"
#include "tcplistener.h"
#include "writer.h"

using namespace std;

int main() {
cout << SETREDFG << "Ian's File Cataloging Software rev 1" << SETWHITEFG << endl;
idmanager discIds = idmanager();
tag tg = tag("hello", 222);
tag tagg = tag("hello", 3);
file *fi = new file("hello");
file *aa = new file("hello", 3);
file *abb = new file("o_O", 4);
tagmanager tagmgr = tagmanager();
cout << tg.id << " " << tagg.id << endl;
cout << "sizeof(tag):" << sizeof(tag) << endl;
cout << "sizeof(file):" << sizeof(file) << endl;
cout << "sizeof(sha256):" << sizeof(sha256) << endl;
cout << "sizeof(jaggedbitarray):" << sizeof(jaggedbitarray) << endl;
cout << "sizeof(bitarray):" << sizeof(bitarray) << endl;
cout << "sizeof(cindex):" << sizeof(cindex) << endl;

tagmgr.addtag(tg);
tagmgr.addtag(tagg);
cout << (tagmgr.tagexists(222) ? "true" : "false") << endl;
cout << (tagmgr.tagexists(3) ? "true" : "false") << endl;
cout << (tagmgr.tagexists(2) ? "true" : "false") << endl;
sha256 a = sha256();
char* bb = new char[32];
sha256 b = sha256(bb);
a.hashfile("filecatalog.cpp");
cout << (a == b ? "true" : "false") << endl;
b.hashfile("filecatalog.cpp");
cout << (a == b ? "true" : "false") << endl;

cindex index = cindex();
index.addfile(aa);
index.addfile(abb);


//index.listfiles();

file* ss;
const char* eees;
for (int i = 0; i < 67; i++) {
	eees = new char[3] { (i/10) + 48, (i % 10) + 48, '\0' };
	ss = new file(eees, i);
//	index.addfile(ss);
}

//index.listfiles();
for (int i = 3; i < 40; i++) {
	index.removefile(i);
}
//index.listfiles();

tag* tdd = index.gettag("loader");
file* ffff = new file("Minecraft Forge");
index.link(index.addfile(ffff), index.addtag("minecraft"));
index.link(ffff, index.addtag("mod"));
index.link(ffff, index.addtag("1.12.2"));
index.link(ffff, index.gettag("mod loader"));
tag* tss = index.gettag("loader");
cout << "tdd == tss:" << (tdd == tss ? "true" : "false") << endl;

index.listfiles();
ofstream ffie;
ffie.open("index.tdb");
binwriter dbw = binwriter(ffie);
database db = database(index, dbw);
db.save();

return 0;
}
