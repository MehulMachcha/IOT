from twython import Twython

# fill in your 4 keys in following variables 
C_key = ""
C_secret = ""
A_token = ""
A_secret = ""

myTweet = Twython(C_key,C_secret,A_token,A_secret)
myTweet.update_status(status="Thanks for reading")

