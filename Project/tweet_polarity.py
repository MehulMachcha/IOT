import re
import sys
import tweepy
from textblob import TextBlob
import collections

# Revemove the special characters in the tweet
def clean_tweet(tweet):
    return ' '.join(re.sub('(@[A-Za-z0-9]+)|([^0-9A-Za-z \t])|(\w+:\/\/\S+)', ' ', tweet).split())

# Calculate the polarity of the tweet
def get_polarity(tweet):
    polarity = TextBlob(clean_tweet(tweet)).sentiment.polarity 
    if polarity > 0 :
        return 'positive'
    elif polarity < 0:
        return 'negative'
    else:
        return 'neutral'

if (len(sys.argv) != 2):
	print("Missing Twitter screen name")
	sys.exit(-1)

consumer_key = ""
consumer_secret = ""
access_key = ""
access_secret = ""

screen_name = sys.argv[1]
auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_key, access_secret)
api = tweepy.API(auth)
tweets = [clean_tweet(tweet._json['text']) for tweet in api.user_timeline(screen_name = screen_name,count=200)]

tweets_polarity = [get_polarity(tweet) for tweet in tweets]

counter = collections.Counter(tweets_polarity)
print(counter)