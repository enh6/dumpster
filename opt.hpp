#ifndef _OPT_H_
#define _OPT_H_
#include <cassert>
#include <string>
#include <vector>

#if 0
int main(int argc, char **argv) {
  Opt opt("opt", "demo of opt.h");
  opt.addOption("file", {"-f", "-F", "--file"}, "specify an input file", 1);
  opt.addOption("help", {"-h", "--help"}, "show this help message", 0);
  if (!opt.parse(argc, argv)) {
    std::cout << opt.errorMessage();
    return 0;
  }
  if (opt["help"]) {
    std::cout << opt.printOptions();
    return 0;
  }
  if (opt["file"]) {
    std::cout << "file: ";
    for (auto &arg : opt["file"]->args) {
      std::cout << arg << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
#endif

class Opt {
public:
  struct Option {
    const std::string name;
    const std::vector<std::string> flags;
    const std::string description;
    const int num_args;

    bool set;
    std::vector<std::string> args;
  };

  Opt(std::string name, std::string desc)
      : _program_name(name), _program_description(desc) {}

  void addOption(std::string name, std::vector<std::string> flags,
                 std::string description, int num_args) {
    assert(flags.size() > 0);
    assert(num_args >= 0);
    for (auto &option : _options) {
      assert(name != option.name);
      for (auto &flag : flags) {
        for (auto &f : option.flags) {
          assert(f != flag);
        }
      }
    }
    _options.push_back({name, flags, description, num_args, false});
  }

  bool parse(int argc, char **argv) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
      args.emplace_back(argv[i]);
    }
    return parse(args);
  }

  bool parse(std::vector<std::string> args) {
    for (auto it = args.begin(); it != args.end(); it++) {
      if (*it == "--") {
        _arguments.insert(_arguments.end(), it + 1, args.end());
        return true;
      } else if ((*it)[0] == '-') {
        Option *opt = getOption(*it);
        if (!opt) {
          _error_message = "Invalid option " + *it + ".\n";
          return false;
        }
        if (it + opt->num_args >= args.end()) {
          _error_message =
              *it + " needs " + std::to_string(opt->num_args) +
              (opt->num_args == 1 ? " argument.\n" : " arguments.\n");
          return false;
        }
        opt->set = true;
        opt->args.assign(it + 1, it + 1 + opt->num_args);
        it += opt->num_args;
      } else {
        _arguments.push_back(*it);
      }
    }
    return true;
  }

  const Option *operator[](std::string name) {
    for (const auto &opt : _options) {
      if (opt.set && opt.name == name) {
        return &opt;
      }
    }
    return nullptr;
  }

  std::string printOptions() {
    std::string ss;
    ss = ss + _program_name + ":\n" + _program_description + "\n\n";
    for (auto &opt : _options) {
      std::string s = opt.flags[0];
      for (int i = 1; i < opt.flags.size(); i++) {
        s = s + ", " + opt.flags[i];
      }
      int indent = s.size() > 28 ? 2 : 30 - s.size();
      s = s + std::string(indent, ' ') + opt.description + "\n";
      ss += s;
    }
    return ss;
  }

  std::vector<std::string> arguments() { return _arguments; }
  std::string errorMessage() { return _error_message; }

private:
  Option *getOption(std::string arg) {
    for (auto &opt : _options) {
      for (auto &flag : opt.flags) {
        if (arg == flag) {
          return &opt;
        }
      }
    }
    return nullptr;
  }

  std::vector<Option> _options;
  std::vector<std::string> _arguments;
  std::string _program_name;
  std::string _program_description;
  std::string _error_message;
};

#endif
