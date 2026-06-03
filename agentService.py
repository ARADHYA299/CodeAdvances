from agents.engineering_agent import engineering_agent
from agents.growth_agent import growth_agent
from agents.product_agent import product_agent
from agents.ux_agent import ux_agent
import json

class AgentService:
  
  def __init__(self , llm):
    self.llm = llm
    
  def safe_parse(self , response):
    try:
      return json.loads(response)
    except:
      return{
        "issue": "...",
        "reason": "...",
        "impact": "...",
        "suggestion": "..."
      }
    

  def run_agents(self, context):
    return {
      "pm": product_agent(self.llm, context),
      "ux": ux_agent(self.llm, context),
      "growth": growth_agent(self.llm, context),
      "engineering": engineering_agent(self.llm, context)
    }