class TimelineService:
  def buildTimeline(self , events):
    timeline = []
    
    click_count = 0
    
    for i , event in enumerate(events):
      time = f"00:{i*5:02d}"
      
      if event["type"] == "click":
        click_count += 1
        
        if click_count > 3:
          timeline.append({
            "time" : time,
            "event" : "Repeated Clicks detected (possible user frustration)"
          })
        else:
          timeline.append({
            "time" : time,
            "event": f"User clicked on {event['target']}" 
          })
      
      elif(event["type"] == "navigate"):
        timeline.append({
          "time":time,
          "event":f"User navigated to {event['target']}"
        })
        
        
    return timeline