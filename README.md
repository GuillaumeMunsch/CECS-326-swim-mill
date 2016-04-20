# CECS-326-swim-mill

The purpose of this project is to create a river in which a fish is going to look for some pellets that are randomly dropped into the river.

The `fish` itself and each `pellet` are processes on their own. They are coordinated by the `swim_mill` process, which is the main one.

A graphical version is also available.

### Version
1.0.0

### Tech

* [C]
* [Ncurses]

### Installation

Install it this way:

```sh
$ git clone https://github.com/LeZohan/CECS-326-swim-mill.git
$ cd CECS-326-swim-mill/
$ make
```

And launch it this way:

```sh
$ ./swim_mill
```

This will look like that:

![](screenshots/no_lib.png?raw=true)

### Graphic part

The graphical part has been developped with the `ncurses` library which can be installed like this:

##### OS X (with Homebrew)

```sh
$ brew install ncurses
```

Once you've done this, compile the graphic part:

```sh
$ make graphic
```

And simply run it this way:

```sh
$ ./swim_mill graphic
```

It looks a bit prettier with the ncurses library:

![](screenshots/ncurses.png?raw=true)

You can customize the map size and the different process cycle times in the `common/utils.h` file !

Made with ♥ by Guillaume Munsch

   [C]: <http://www.cprogramming.com>
   [Ncurses]: <http://linux.die.net/man/3/ncurses>