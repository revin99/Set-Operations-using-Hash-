# Set-Operations-using-Hash-

User-interactive programme to create sets and initialise them wih values according to the user.
The elements in a particular set are stored in the form of a Hash Table, governed by a string mapping function.

The **string-polynomial rolling hash function**:- 
 hash(s)=(s[0]+s[1]⋅p+s[2]⋅p2+...+s[n−1]⋅pn−1) modm 
        =( ∑{i=0,n−1} s[i]⋅pi)modm 
        
The functionalities supported between two sets are of union, interesection , difference and finding if one is a complete subset of another.
