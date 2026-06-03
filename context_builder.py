class TranscriptCleaner:
  def clean(self, transcript):
    if transcript is None:
      return ""
    return str(transcript).strip()


class EventExtractor:
  def extract(self, events):
    if events is None:
      return []
    if isinstance(events, list):
      return events
    return [events]


class EventFlowBuilder:
  def build(self, extracted_events):
    flow = []
    for idx, event in enumerate(extracted_events):
      flow.append({"step": idx + 1, "event": event})
    return flow


class FlowBuilder:
  def __init__(self, cleaner=None, extractor=None, flow_builder=None):
    self.cleaner = cleaner or TranscriptCleaner()
    self.extractor = extractor or EventExtractor()
    self.flow_builder = flow_builder or EventFlowBuilder()

  def build(self, transcript, events):
    cleaned_transcript = self.cleaner.clean(transcript)
    extracted_events = self.extractor.extract(events)
    flow = self.flow_builder.build(extracted_events)

    context = {
      "transcript": cleaned_transcript,
      "flow": flow
    }

    return context