# CampaignTargeting
The Campaign Targeting project enables user to find the correct campaign based on his provided choice of campaign segments.
The program takes a single argument, a file containing a list of campaigns. Once the program has loaded the data file, it will start accepting input from users.

Step by step running of the program:
Step 1:
The program first accepts and loads the campaign list file for reading.
The program accepts single file as an argument from the user.

Step 2:
The program first displays a map of campaign all the segments and its associates campaigns.
It then accepts user input i.e. segments.
The user should enter the input segments in the form of numbers. For eg. 3 4 10.
Note – No commas (,) or a delimiter other than space should be used.

Step 3:
Once the user enters his input, his input is split into string vector based on the provided delimiter.
The program will then return the most appropriate campaign for the provided user segments.
The program will keep accepting input from the user until the user exits by pressing ‘n’.


Approach used:
Case 1. 
When user enters campaign segments, his input is split into string vector.
The program associates every segment to its respective campaign and maintains the count of each campaign. The campaign with highest count is returned to the user.
For eg. 3 4 5 10 2 200
User input		Associated campaign		  Count
3 4 10 2		      campaign_a			  count - 4
3			            campaign_b			  count - 1
3 4 200			      campaign_c			  count – 3

Highest count campaign - campaign_a

Case 2.
In order to deal with the issue of the campaign starvation, I have used an approach to maintain the count of the campaign and return the campaign with least count to the user.
For eg. The segment 3 is present in all 3 campaigns. We don’t want only one single campaign to be associated with it and starve two other campaigns. So, I maintain the count of campaigns every time it’s associated segment is provided by the user and return the campaign with least count.

User input		Associated Campaigns		Count
     3			    campaign_a				      0
                campaign_b				      0
                campaign_c				      0
Output – Since the count of all the campaigns is same, a random campaign out of the three is returned. Let’s assume, it returns campaign_c.


User input		Associated Campaigns		Count
      3			      campaign_a				     0
                  campaign_b				     0
                  campaign_c				     1
Now, the user input again is 3. So, the program will return either campaign_a or campaign_b since count(campaign_a) = count(campaign_b).


Case 3.
When user passes segments which are not associated with any campaign, the program returns the output as: Campaign not found.


Technologies used:
Programming language – C++14
Compiler – Cygwin GCC5.0
IDE – Clion 2018.2


Steps to run the program:
Step 1:
Enter name (or path) of the text file as an argument to run the program.
Note – The program accepts both absolute and relative path

Step 2:
Enter inputs with space between them.
For eg. 3 4 10

Step 3:
Once you are done testing all the input you can exit the program.
Press n to exit.
