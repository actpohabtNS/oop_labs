IMPLEMENTED
===========
HoverTableView		| Passes hovered QModelIndex to HoverRowDelegate

HoverRowDelegate	| Highlight hovered row

MoviesDelegate		| Draws controls (move, edit, delete) for row when it is hovered

MoviesFilterProxyModel	| Sorts, Filters and Counts total time watched

MoviesSeenModel		| Just models for Movies
MoviesToSeeModel	|

mainwindow		| Controls user input, checks it, conduct changes in model depending on user's actions


Moviefy
===========

Provides such greatful capabilities as:

○ SEEN MOVIES
• Specify:
	• The title
	• Your rate (1 - 10)
	• Genre (from predefined list that can be searched) !can be more that 1 genre!
	• Short description
	• Special group (created by user, can specify smth about film (e.g. music, effects etc.), can be searched)
	• Length (optional)
	• Date of adding !set automatically!

• Films can be searched by genre and special group
• Can be sorted by name, rate, length
• Can be edited, deleted
• Total number of time watched is calculated for the whole list
• All the data is saved to a file
• Export one film or all list into a text / file
• Import films from a text / textfile with predifined or set markdown (if smth is not clear - it is left unfilled)


○ TO SEE MOVIES
• Specify:
	• The title
	• Genre (from predefined list that can be searched) !can be more that 1 genre! (optional)
	• Short description  (optional)
	• Length (optional)
	• Date of adding !set automatically!

• Films can be searched by genre
• Can be sorted by name, length
• Can be edited, deleted
• Total number of time to watch is calculated for the whole list
• Move movie from TO WATCH to WATCHED with one click
• All the data is saved to a file
• Export one film or all list into a text / file
• Import films from a text / textfile with predifined or set markdown (if smth is not clear - it is left unfilled)