## ---------------------------------------------------------------------
##
## Copyright (C) 2014 - 2018 by the deal.II authors
##
## This file is part of the deal.II library.
##
## The deal.II library is free software; you can use it, redistribute
## it, and/or modify it under the terms of the GNU Lesser General
## Public License as published by the Free Software Foundation; either
## version 2.1 of the License, or (at your option) any later version.
## The full text of the license can be found in the file LICENSE.md at
## the top level directory of deal.II.
##
## ---------------------------------------------------------------------

#
# A PERL script that modifies the default-generated 'header.html' file
# that doxygen provides for us and customizes it for our needs.
#


if (m'</head>')
{
    print '<link rel="SHORTCUT ICON" href="deal.ico"></link>', "\n";
    print '<script type="text/javascript" src="$relpath^custom.js"></script>', "\n";
    print '<meta name="author" content="The deal.II Authors <authors@dealii.org>"></meta>', "\n";
    print '<meta name="copyright" content="Copyright (C) 1998 - 2021 by the deal.II authors"></meta>', "\n";
    print '<meta name="deal.II-version" content="10.0.0-pre"></meta>', "\n";

    # This script is run with  -pi, so it outputs every line we don't
    # explicitly modify. Consequently, it still outputs the '</head>' tag
    # above.
}

s/\$projectname// unless (m/<title>/);

# Finally, define some extra commands for MathJax in every file. These are in an
# undisplayed div so that the \newcommand text does not pop up and then
# disappear while MathJax works.
#
# Note: If you add an entry here, also put it into ./doc/doxygen/extra.sty
if (eof)
{
    print '<!--Extra macros for MathJax:-->', "\n";
    print '<div style="display:none">', "\n";
    print '\(\newcommand{\dealvcentcolon}{\mathrel{\mathop{:}}}\)', "\n";
    print '\(\newcommand{\dealcoloneq}{\dealvcentcolon\mathrel{\mkern-1.2mu}=}\)', "\n";
    print '\(\newcommand{\jump}[1]{\left[\!\left[ #1 \right]\!\right]}\)', "\n";
    print '\(\newcommand{\average}[1]{\left\{\!\left\{ #1 \right\}\!\right\}}\)', "\n";
    print '</div>', "\n";
}
