### PathGenerator's Bugs:
 - When Initializing PathGenerator's WayPoints sending `Point{ 0_in, 0_in }` will result in nothing happening despite compiling fine.
 - `PathGenerator::generatePath( PathGenerator::PathType::StraightInterpolation )` doesn't work

### PurePursuit's Bugs:
 - When using PurePursuit's `findNearestPoint()` method, the point sent *has* to be within one lookaheadDistance to any point on the path. Otherwise it will not do anything. 

And that's all for our bugs... hopefully. If you find a bug edit this file on [github](https://github.com/team914/autolib) and create a PR. For instructions on how to do that... ping me on the Vex Unofficial Discord *potatehoes#7782* or email me *acetousk@gmail.com*
