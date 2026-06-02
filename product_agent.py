import json 
def product_agent(llm , context):
  prompt = f"""
You are a Product Manager.

Analyze this user behavior:

{context}

Return ONLY in JSON format:

{{
  "issue": "...",
  "reason": "...",
  "impact": "...",
  "suggestion": "...",
  "severity": 1-10,
  "confidence": 0.0-1.0
}}

rules:
- severity = importance of issue
- confidence = confidence in your diagnosis
- return ONLY JSON
"""
  
  response = llm(prompt)
  return json.loads(response)

