#ifndef _url_h_
#define _url_h_

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class URL {
private:
  // Private vars to hold URL
  string protocol;
  string hostname;
  int port;
  vector<string> path;

public:
  // Default constructor
  URL() {
    protocol = "http";
    hostname = "localhost";
  }
  // Constructor with URLString
  URL(string urlStr) { set(urlStr); }
  // Set object vars by parsing URLString
  void set(string urlStr) { URL::parse_url(urlStr); }
  // Get a URLString from the object vars
  string get() const {
    string str = "";
    str.append(protocol);
    str.append("://");
    str.append(hostname);
    if (protocol == "http") {
      if (port != 80) {
        str.append(":");
        str.append(to_string(port));
      }
    } else if (protocol == "https") {
      if (port != 443) {
        str.append(":");
        str.append(to_string(port));
      }
    } else if (port != -1) {
      str.append(":");
      str.append(to_string(port));
    }
    str.append(create_path(path));
    return str;
  }

  string get_proto() const { return protocol; }
  string get_host() const { return hostname; }
  int get_port() const { return port; }
  string get_path() const { return create_path(path); }

  void set_proto(string proto) {
    if (proto != "http" && proto != "https") {
      throw std::invalid_argument("Hostname must be either http or https.");
    }
    protocol = proto;
  }
  void set_host(string host) { hostname = host; }
  void set_port(int portNo) {
    if (portNo > 0 && portNo < 65536) {
      port = portNo;
    } else {
      throw std::invalid_argument("Port must be in the range 1 to 65535.");
    }
  }
  void set_path(string pathStr) {
    if (pathStr[0] != '/') {
      pathStr = "/" + pathStr;
    }
    path = separate_path(pathStr);
  }

  void up() {
    if (path.size() > 0) {
      path.pop_back();
    }
  }

  void up(int num) {
    for (int i = 0; i < num; i++) {
      up();
    }
  }

  void rel(string newUrl) {
    // Completely replace URL
    if (newUrl.find("://") != -1) {
      set(newUrl);
    } else if (newUrl[0] == '/') {
      set_path(newUrl);
    } else {
      if (path.size() > 0) {
        path.pop_back();
      }
      path = separate_path(create_path(path) + "/" + newUrl);
    }
  }

private:
  // Internal method to set object vars from a URLString
  void parse_url(string str);

  // Internal method to separate a pathstring by slashes
  vector<string> separate_path(string pathStr) {
    vector<string> vec;
    bool parseFinished = false;
    while (!parseFinished) {
      int slashIndex = pathStr.find('/');
      string str = pathStr.substr(0, slashIndex);
      if (str.length() > 0 && str != ".") {
        if (str == "..") {
          if (vec.size() > 0) {
            vec.pop_back();
          }
        } else {
          vec.push_back(str);
        }
      }
      pathStr = pathStr.substr(slashIndex + 1, -1);
      if (slashIndex == -1)
        parseFinished = true;
    }
    return vec;
  }

  // Internal method to create a pathstring
  string create_path(vector<string> arr) const {
    string str = "";
    for (vector<string>::iterator i = arr.begin(); i != arr.end(); ++i) {
      str.append("/");
      str.append(*i);
    }
    return str;
  }
};

#endif