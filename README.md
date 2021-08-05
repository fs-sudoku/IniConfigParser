# IniConfigParser

A simple .Ini Parser

Example.cpp:

```C#
IniConfig config("Example.ini");
std::string variable = config.GetVariable("some_variable").AsString();

std::cout << variable << std::endl; // prints: 100
```

Example.ini:

```ini
[some_sector]
some_variable = 100 ; this is some comment
```

Output:

```ini
100
```
