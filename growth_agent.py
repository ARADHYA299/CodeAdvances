import json

def growth_agent(llm , context):
  
  prompt = f"""
  
  You are a growth strategist
  
  Analyze this:
  {context}
  
  Return ONLY in JSON format:
  {{
    "issues": "...",
    "reason": "...",
    "impact": "...",
    "suggestion":"...",
    "Severity":1-10,
    "confidence":0.0-1.0
  }}
  """
  
  
  response = llm(prompt)
  return json.loads(response)