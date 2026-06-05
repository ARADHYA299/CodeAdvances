class synthesisService:
  
  def __init__(self , llm):
    self.llm = llm

  def synthesize(self, agentOutputs):
    prompt = f"""
    You are a moderator.

    combine these insights:
    {agentOutputs}

    Give:
      - key issues
      - quick fixes
      - strategic improvements
    """

    return self.llm(prompt)