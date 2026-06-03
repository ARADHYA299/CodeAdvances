from dotenv import load_dotenv # type: ignore
import os
load_dotenv()

from fastapi import APIRouter
from services.context_builder import FlowBuilder
from services.agentService import AgentService
from services.gemini_llm import GeminiLLM
from services.SynthesisService import synthesisService
from models.request import AnalyzeRequest
from models.response import AnalyzeResponse
from services.timelineService import TimelineService
router = APIRouter()

api_key = os.getenv("GEMINI_API_KEY")

if not api_key:
    raise ValueError("GEMINI_API_KEY not found in environment")

llm = GeminiLLM(api_key=api_key)  

flow_builder = FlowBuilder()
agent_service = AgentService(llm)
synthesis_service = synthesisService(llm)
timelineService = TimelineService()

@router.post("/analyze" , response_model=AnalyzeResponse)
def analyze(data : AnalyzeRequest):
  context = flow_builder.build(
    data.transcript,
    data.events
  )
  
  
  agentOutput = agent_service.run_agents(context)
  
  summary = synthesis_service.synthesize(agentOutput)
  
  timeline = timelineService.buildTimeline(data.events)
  
  return{ 
    "agents":agentOutput,
    "summary":summary,
    "timeline":timeline
  }
@router.get("/test-gemini")
def test_gemini():
    response = llm("Say hello in one sentence.")
    return {"response": response}
  
api_key = os.getenv("GEMINI_API_KEY")

print("API KEY PREFIX:", api_key[:10])