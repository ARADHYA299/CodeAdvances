from pydantic import BaseModel
from typing import Dict


class AgentInsight(BaseModel):
  issue:str
  impact:str
  suggestion:str
  severity:int
  confidence:float

class AnalyzeResponse(BaseModel):
  agents : Dict[str, AgentInsight]
  summary : str
  timeline : list[Dict[str , str]]
  
  
  