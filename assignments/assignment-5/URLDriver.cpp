#include "url.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

/*
 * This prints out the URL and all its parts.
 */
void dump_url(string label, const URL &url) {
  string gotten = url.get();
  std::cout << "=== " << label << ": " << gotten << " ===" << std::endl;
  std::cout << "  protocol: " << url.get_proto() << std::endl;
  std::cout << "      host: " << url.get_host() << std::endl;
  std::cout << "      port: " << url.get_port() << std::endl;
  std::cout << "      path: " << url.get_path() << std::endl;
  if ((url.get_proto() == "http" && url.get_port() == 80 &&
       gotten.find(":80") != string::npos) ||
      (url.get_proto() == "https" && url.get_port() == 443 &&
       gotten.find(":443") != string::npos))
    std::cout << "** Note: Should suppress default port "
              << "number here. **" << std::endl;
  std::cout << std::endl;
}

int main() {
  // A test url.
  URL u1("http://www.cplusplus.com/reference/set/multiset");
  dump_url("first test", u1);

  // And we can change all this stuff by parts.
  u1.set_proto("https");
  u1.set_host("feeble.server.biz");
  u1.set_port(8080);
  u1.set_path("/this/place/here.html");
  dump_url("modified", u1);

  // A few more to test test parsing the URL string and printing details.
  dump_url("parse1", URL("https://someplace.else"));
  dump_url("parse2", URL("http://www.next.tuesday:8080/help/"));
  dump_url("parse3", URL("http://somewhere.nice.com:80/smoo/foo/bar/baz"));
  URL uu("https://www.near.and:443/far/away");
  dump_url("parse4", uu);
  uu.set("https://home/");
  dump_url("parse5", uu);

  // Well, let's try some bad ones.  You should see four messages
  // from a caught exception, but the program should not crash.
  std::cout << "=== Checking throws: should see some messages ===" << std::endl;
  for (auto s : {"completely bogus", "htttp://baaaad/protocol/land",
                 "http:/this/too", "http://www.bad.port:927113/"}) {
    try {
      URL bad(s);
      std::cout << "  *** You should not be seeing this [" << s << "] ***"
                << std::endl;
      dump_url("broken url", bad);
    } catch (std::invalid_argument &ie) {
      std::cout << "  " << s << ": got expected invalid_argument "
                << "exception: " << ie.what() << std::endl;
    }
  }

  string s = "http://abc.cleveland.place:portland/here/too";
  try {
    uu.set(s);
    std::cout << "  *** You should not be seeing this "
              << "set(" << s << ")" << std::endl;
    dump_url("bad set", s);
  } catch (std::invalid_argument &ie) {
    std::cout << "  set(" << s << "): got expected "
              << "invalid_argument exception: " << ie.what() << std::endl;
  }

  // Some bad sets.  Should see catch messages.
  URL badset("http://www.nice.server/dingbat");
  try {
    badset.set_proto("bogus");
    std::cout << "  *** You should not be seeing this "
              << "(set_proto(\"bogus\")) ***" << std::endl;
    dump_url("bad protocol set", badset);
  } catch (std::invalid_argument &ie) {
    std::cout << "  set_proto(\"bogus\"): got expected "
              << "invalid_argument exception: " << ie.what() << std::endl;
  }

  try {
    badset.set_port(-481);
    std::cout << "  *** You should not be seeing this "
              << "(set_port(-481)) ***" << std::endl;
    dump_url("bad port set", badset);
  } catch (std::invalid_argument &ie) {
    std::cout << "  set_port(-481): got expected "
              << "invalid_argument exception: " << ie.what() << std::endl;
  }
  std::cout << std::endl;

  // Let's try out the operations.
  URL u2("http://sandbox.mc.edu/~bennet/cs404b/outl/arrcomp.html");
  std::cout << "=== up test: " << u2.get() << " ===" << std::endl;
  u2.up(2);
  std::cout << "=== after up(2): " << u2.get() << " ===" << std::endl;
  u2.up();
  std::cout << "=== after up(): " << u2.get() << " ===" << std::endl;
  u2.up(3);
  dump_url("up(3) more (all gone)", u2);

  // Let's try rel(), all three cases.
  URL u3("http://www.outa.site.com/here/is/nice");
  std::cout << "=== starting rel(): " << u3.get() << " ===" << std::endl;
  u3.rel("a/good/spot");
  std::cout << "=== over rel: " << u3.get() << " ===" << std::endl;
  u3.rel("/some/other/place");
  std::cout << "=== rel path replace: " << u3.get() << " ===" << std::endl;
  u3.rel("https://www.google.com");
  dump_url("rel full replace", u3);

  // Some hard paths.  Recall that a . component is to be removed,
  // and a .. component removes the previous one.  An empty segment
  // (multiple slashes together) is ignored.
  //    https://www.un.sitely/good/ugly
  std::cout << "=== hard1 === "
            << URL("https://www.un.sitely/good/bad/../ugly").get() << std::endl;
  //    http://www.un.likely/johnson
  std::cout << "=== hard2 === "
            << URL("http://www.un.likely/smith//jones/../../johnson").get()
            << std::endl;
  //     http://www.un.warrented/left/right/down
  std::cout
      << "=== hard3 === "
      << URL("http://www.un.warrented/../left///right/./down/there/..").get()
      << std::endl
      << std::endl;

  // Now, on rel(), the .. is supposed to cross from the argument to
  // the original path.  In fact, this is one of the main uses of
  // relative URLs.
  URL u4("http://www.yyy.zzz.com/some/place/else");
  u4.rel("../better/location");
  //    http://www.yyy.zzz.com/some/better/location
  std::cout << "=== rel() .. 1: " << u4.get() << " ===" << std::endl;
  //    http://www.yyy.zzz.com/over/instead.html
  u4.set("http://www.yyy.zzz.com/some/place");
  u4.rel("../../../over/here/../instead.html");
  std::cout << "=== rel() .. 2: " << u4.get() << " ===" << std::endl;
}