=====================
 Random C++ projects
=====================

Here is a collection of some random projects I made in C++/Qt on the
course of the years, mostly to learn the language. I was young and
stupid, so some might be pretty low-quality and/or plain dumb.

bruteRace
=========

A wikipedia race is when you try to find the shortest path between two
given wikipedia pages.

A bruteforce crawler for wikipedia races. It uses Qt's asynchronous requests to make a lot requests in parallel, resulting in a breadth-first search that's pretty inefficient in term of memory.

garbage
=======

The IT of my school used to set the default passwords to the people's
birthday dates. Of course, those birthday dates where available in the
yearbook, so a quick scrapper was able to find them and to test them
against the pop server.

But just outputting passwords on the command line is not
fun. Hollywood thought us a few things about password and database:

- When search in a database, every photo should be displayed as fast
  as possible.
- Passwords must be cracked character after character, displaying a
  lot of random characters in the process.

`libgarbage` is a library that provides an interface that implements theses rules, and `garbagecollector` uses this library on the previously described problem to provide a hollywood-approved password collecting experience.

newton
======

Bouncing balls. But without a proper physics engine, so quite boring
actually.

qfilets
=======

A graph : edges and arcs. You must move the edges so that no two arcs
intersect. This game was so captivating that I couldn't develop it
further than the victory condition check : any attempt to resume development resulted in hours of playing it.

qftpindexer
===========

Visits a given list of ftp servers and list all files that are younger
than a week. I presume it was used for semi-legal purposes at the
time.

The code is a precursor to `burgos`_

.. _`burgos`: https://github.com/madjar/burgos

qook
====

The first prototype of one of my recurrent side project : the meal
organizer. Select a date range and place meals on it. The idea was to
then generate and shopping list and to recommend meals, but I never
got to that part. Further prototypes where developed in python/web.

whoIsUp
=======

A basic monitoring system that takes xml files as input. We were proud
of this at the time. Those where the day.

yoshisearch
===========

Yoshi_ is a ftp indexer and search engine, and it provided an ad-hoc api. This prototype use that api to provide on-the-fly incremental search.

.. _Yoshi : http://sourceforge.net/projects/yoshiindexer/
