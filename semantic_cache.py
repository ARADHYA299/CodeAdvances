import numpy as np
from sentence_transformers import SentenceTransformer
from sklearn.metrics.pairwise import cosine_similarity

class SemanticCache:
  
  def __init__(self , threshold = 0.85):
    self.model = SentenceTransformer('all-MiniLM-L6-v2')
    self.threshold =  threshold
    self.cache = []
    
    self.hit_count = 0
    self.miss_count = 0
  
  
  def embed_query(self , query):
    return self.model.encode(query)

  
  def lookup(self,query):
    query_vector = self.embed_query(query)
    
    best_score = 0
    best_entry = None
    
    for entry in self.cache:
      score = cosine_similarity([query_vector],[entry["embedding"]])[0][0]
      
      if score > best_score:
        best_score = score
        best_entry = entry
      
    if best_score >= self.threshold:
      self.hit_count += 1
        
      return True , best_entry , best_score
      
    else:
        self.miss_count += 1
        return False , None , None
  
  def add(self, query , response , cluster):
    embedding = self.embed_query(query)
    
    entry = {
      "query" : query,
      "result" : response,
      "embedding" : embedding,
      "cluster" : cluster
    }
    
    self.cache.append(entry)
    
  def stats(self):
    total = len(self.cache)
    
    if total == 0:
      hit_rate = 0
    else:
      hit_rate = self.hit_count / (self.hit_count + self.miss_count)
      
    return{
      "total_entries" : total,
      "hit_count" : self.hit_count,
      "miss_count" : self.miss_count,
      "hit_rate" : hit_rate
    }
    
  def clear(self):
    self.cache = []
    self.hit_count = 0
    self.miss_count = 0