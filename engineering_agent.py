import json

def engineering_agent(llm, context):
  
  prompt = f"""
  
  You are a Software Engineer
  
  Analyze:
  {context}
  
  {{
    "issue": "...",
    "reason": "...",
    "impact": "...",
    "suggestion": "...",
    "Severity": 1-10,
    "confidence": 0.0-1.0
  }}
  """
  
  response = llm(prompt)
  
  return json.loads(response)