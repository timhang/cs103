CSCI 103 Programming Assignment 2, Chroma Key, Fall 2014

Name: Weihang Zhang

Email Address: weihangz@usc.edu

NOTE: You can delete the questions, we only need your responses.

=============================== Prelab =======================================

Pixel                |    RGB Value     |  Distance from Chroma Key
-------------------------------------------------------------------
Top-left background  | ( 69  ,  138  ,  19  )|  n/a
Arm                  | (  255 , 159  , 114  )| 209.91
Vest                 | ( 26  ,  28  , 23 )   | 118.17
Shirt                | ( 250  , 211   , 238 )| 293.34

================================== Review ===================================
1. Discuss and justify which pixels you chose to compute the average 
background value for method 1. Was there a reason not to choose more or
fewer pixels?

Response 1: I chose the top-left 40x40 square as the background sample to compute the
average in method 1. Choosing less would result in inaccuracy due to shadows
and shades; choosing more has the danger of overlapping with the center image.

2. For method 1, do some experiments to find the range of distance thresholds 
for which the program seems to operate the best. You may use different 
thresholds for the two different sample images (Colbert and Bird). 
Note: threshold values that are too low will cause certain portions of the 
chroma key to stay in the picture; values that are too high will cause parts 
of the foreground image to disappear.

Response 2: for colbert, 80 seems to work well. For bird, 80 works as well.
For astro, 67 is around the optimal value, and for faded colbert, 15 seems
to work best.

  Image                  Min Threshold           Max Threshold
  Colbert range:  from     77            to       81
  Bird range:     from     55            to       85


3. For method 2, explain what you implemented and why.  How did you go about 
implementing it? Walk us through a high-level description of what you did in 
your code (and use comments in the actual .cpp file to fill in the details). 
What other alternatives did you consider either before or after you
implemented your selected method?  What are the relative pros and cons of 
these methods? [This question is open-ended!]

Response 3: I found the standard deviation of the set of data that stores the
distance between each pixel to the average of the top-left sample square; call it stdv. 
Then, I calculated the average RGB value of every pixel, and find the distance
between this value and the average RGB value of the sample square; call it allavg.

Last, I manipulate the standard deviation in a way that when it is stdv/allavg>2,
the threshold value would be adjusted high than the standard deviation;
when stdv/allavg <=2, the threshold value would be adjusted to higher
or equal to the standard deviation.

I implemented this method because I believe it can process a wide range
of pictures, especially if they are low in contrast like in the faded image.
Standard deviation adjusts the threshold value based on the variation in the
data set therefore is more reliable than using a constant scale for all picture.

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

:

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

:

Do you have any other remarks?

:
