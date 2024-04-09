#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "url.h"

void URL::parse_url(string str) {
  // Extract the protocol from the URLString
  int protoSeperate = str.find("://");
  if (protoSeperate == string::npos) {
    throw invalid_argument("Didn't find a protocol.");
    return;
  }
  protocol = str.substr(0, protoSeperate);
  // Remove the protocol, leaving just the hostname, port, and path
  str = str.substr(protoSeperate + 3, -1);
  if (str.length() < 1) {
    throw invalid_argument("URL length is not sufficient.");
    return;
  }
  // Check for a specified port
  int portIndex = str.find(":");
  int pathStart = str.find('/');
  if (portIndex == string::npos) {
    // No specified port, automatically set based on protocol
    if (protocol == "http") {
      port = 80;
    } else if (protocol == "https") {
      port = 443;
    } else {
      throw invalid_argument("URL length is not sufficient.");
      return;
    }
    hostname = str.substr(0, pathStart);
    if (hostname.length() < 1) {
      throw invalid_argument("URL length is not sufficient.");
      return;
    }
  } else {
    // Use specified port
    set_port(stoi(str.substr(portIndex + 1, pathStart - portIndex - 1)));
    hostname = str.substr(0, portIndex);
  }
  string pathStr = str.substr(pathStart + 1, -1);
  path = URL::separate_path(pathStr);
}