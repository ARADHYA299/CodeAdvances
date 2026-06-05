import google.generativeai as genai 

class GeminiLLM:
    def __init__(self,api_key :str): 
      genai.configure(api_key=api_key)
      self.model = genai.GenerativeModel("gemini-2.0-flash")
      
    def call(self , prompt : str):
      
      try:
        response = self.model.generate_content(prompt)
        return response.text

      except Exception as e:
        print(e)
        
        return """
      {
        "issue":"Quota exceeded",
        "impact":"Temporary",
        "suggestion":"Retry later",
        "severity":1,
        "confidence":1.0
      }
      """
        
    def __call__(self , prompt : str):
      return self.call(prompt)