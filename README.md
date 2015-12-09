# MyBilliards

Investigation and application of physics in billiards

Research and investigation, physics in billiards

To understand the physics required it is important to begin with the fundamental principles used. In this respect, Newton’s Laws of Motion provides a good starting point as they are very important in the study of mechanics in general.Newton’s laws of motionOn July 5th 1687, Sir Isaac Newton put forth his philosophies on mechanics in his Philosophiӕ Natralis Principia Mathematica. In this work, Newton stated his three laws of motion which are surmised here:
  i.  In the absence of a force, a body either is at rest or moves in a straight line at constant speed.
  ii. A body experiencing a force F experiences an acceleration a related to F by F=ma, where m is the mass of the body. Alternatively,        force is proportional to the time derivative of momentum.
  iii.Whenever a first body exerts a force F on a second body, the second body exerts a force –F on the first body. F and –F are equal in       magnitude and opposite in direction.
These laws form the basis for much of the analysis in the field of mechanics. Of particular relevance to this project is Newton’s 2nd Law, which will be examines in greater detail as it is referred to over the course of this document.

Collisions

Much of the game’s physics focuses on collisions and collision detection. In billiards, striking the cue ball, a ball rebounding against the table rails and a ball hitting another ball will involve some form of collision and collision response, thus being able to accurately simulate these collisions is paramount.For the purpose of this project it will be assumed the collisions between billiard balls are perfectly elastic, it will also be assumed that the balls are rigid bodies and collisions between them will be treated as such.

Impulse 

Generally speaking, impulse can be defined as an average force applied through time. Specifically it is a vector quantity equal to the change in momentum.To calculate the impulse of an object given its mass, final speed and the amount of time which an external force is applied is as follows:
  Impulse(I)=F(∆t)=mv1
This formula will allow us to calculate the initial speed of an object, such as a billiard ball, given the objects mass and the external force applied.For instance, you strike the cue ball of mass 0.15kg with a force of 10N. The force is applied over a period of 0.2 seconds. The initial speed of the ball is calculated as follows:
  F(∆t)=mv
  10(0.2)=0.15v
  2=0.15v
  v=13.33ms−1
Using this formula, it will be possible to determine the initial speed of the cue ball after it has been stuck.
