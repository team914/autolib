# AutoLib

**Summary** 

AutoLib is a Pros C++ Library based off of OkapiLib for Advanced Vex Autonomous Programming. 
 
*Note: AutoLib v1.0.0 is coming out soon! And we would love your contributions! Click to [contact us](https://github.com/team914/autolib#contact).* 

## Why AutoLib?

### Features:
 - PathGenerator: A simplified easy class for generating a path
 - PurePursuit: A robust path following algorithm for controlling your robot's chassis
 - Versatile: You can use your own custom library or you can use OkapiLib to handle the motor control and odometry
 - Documentation: Great Documentation for Expert to Newbie Vex Team Programmers
 - Open Source: You can and should contribute to this project
 
## Docs
Head over to the documentation website:

[https://github.com/team914/autolib/wiki](https://github.com/team914/autolib/wiki)

*Note: The docs are currently in progress, so if you can't find something please [contact us](https://github.com/team914/autolib#contact)!*

## Contributing
AutoLib isn't perfect; and it never will be, but we can get it pretty close. However, without your contributions and community involvment it may never get to it's full potential. So help make AutoLib by submitting a PR.

Contributions are
accepted using GitHub pull requests; for more information, see 
[GitHub documentation - Creating a pull request](https://help.github.com/articles/creating-a-pull-request/). In addition, dealing with git branches and forks can be tricky if you don't already know how to use them; see [Editing and Creating a new branch with git and manage branches](https://github.com/acetousk/autolib/wiki/Editing-Create-a-new-branch-with-git-and-manage-branches)

For a good pull request, we ask you provide the following:

1. Include a clear description of your pull request in the description with the basic "what" and "why"s for the request.
2. If the pull request is a new feature, please include appropriate documentation in the wiki.
3. Keep a consistent coding style.

## Implimentation

### Dependancies
 - OkapiLib's branch [feature/odometry](https://github.com/OkapiLib/OkapiLib/tree/feature/odometry)

 *Note: Make sure that you install okapi's **feature/odomtry** branch rather than some other branch.*

### Robot
We suggest that you use a robot similair to the one described in the 5225A Pilons Position Tracking [Document](https://github.com/OkapiLib/OkapiLib/tree/feature/odometry), however we support basically any configuration of a Skid Steer or X Drive.

*Note: Before you begin to use AutoLib we suggest that you [read up](https://github.com/team914/autolib/wiki/Basic-Autonomous-Tiers-Theory) on the algorithms that we use.*

### Code
```cpp
//This will construct the PathGenerator class
PathGenerator pathGenerator(
{
  //The first point is, by default, automatically 0, 0
  autolib::Point{ -1_ft, 1_ft }, //This generates a Point at ( -1 foot, 1 foot )
  autolib::Point{ 0_ft, 2_ft },  //Then ( 0 feet, 2 feet )
  autolib::Point{ 1_ft, 1_ft },  //Then ( 0 feet, 2 feet )
  autolib::Point( 1_in, 1_in )   //Then ( 1 inch, 2 inches )
  //You can send any number of points along your path.
}, .1_in /**This is the distance between each point after you generate a path. 
          * The more points the better, however more points will take longer 
          * to setup in pre auton.
          */
);

/**This will generate a series of points based off an algorithm. 
 * Currently only HermiteSpline is supported. To figure out how this algoritm works, 
 * we suggest you check this desmos graph out. https://www.desmos.com/calculator/h2jshqzjdo
 */
pathGenerator.generatePath( PathGenerator::PathType::HermiteSpline );

//This will construct the PurePursuit class
PurePursuit purePursuit( 
  pathGenerator.getPath(), // this will send the path from the PathGenerator to PurePursuit
  4_in                     // this is the Pure Pursuit Algorithm's lookaheadDistance
);

/**This should be run in a loop during auton. This uses okapi's odometry feature to 
 * identify the current global x, y, and yaw of the robot. This data is extremely vital 
 * to the Pure Pursuit Algorithm. If this data is signifigantly off the actual position, 
 * then it can and probaly *will* mess up your auton.
 */
purePursuit.getGoalCurvature( 0_ft, 0_in, 0_rad );

```
## Contact

To contact us:
 - Ping @potatehoes#7782 on the [Unofficial Vex Discord Server](https://discord.gg/EpPejXk)
 - Email acetousk@gmail.com
 - PM us on the [Vex Forum](https://www.vexforum.com/u/potatehoes914m)
 
## License

AutoLib is licensed under the Mozilla Public License 2.0.
