import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        self.positives = []
        positive_count=0
        with open(positives) as positive_file:
            for line in positive_file:
                if line.startswith(';') == False:
                    strip = line.rstrip("\n")
                    self.positives.append(strip)
        del self.positives[0]

        self.negatives = []
        negative_count=0
        with open(negatives) as negative_file:
            for line in negative_file:
                if line.startswith(';') == False:
                    strip = line.rstrip("\n")
                    self.negatives.append(strip)
        del self.negatives[0]


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        score = 0

        #separate words in tweet
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        #print(tokens)

        #positive scoring
        for word in tokens:
            for i in range(len(self.positives)): 
                if word == self.positives[i]:
                    score += 1
        
        #negative scoring
        for word in tokens:
            for i in range(len(self.negatives)): 
                if word == self.negatives[i]:
                    score -= 1
                    
        #return score value
        return score
