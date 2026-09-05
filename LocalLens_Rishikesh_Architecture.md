# LocalLens — Rishikesh Edition

### Multi-Agent Civic Information Assistant — Project Architecture

\---

## 1\. Problem Statement

Tourists, foreign yoga/pilgrimage students, migrant workers, and new residents in Rishikesh struggle to find accurate, current, official information on civic services (visa/FRRO registration, local transport, healthcare access, tenant basics) because it is scattered across multiple government portals, often outdated, and hard to navigate in English or other languages.

**Target users:** foreign tourists/yoga students, new residents, migrant workers, students.

**MVP category scope:** (2 categories to start)

1. Foreign tourist / visa (FRRO) registration
2. Local transport (bus routes \& passes)

*(Expand later to healthcare access and tenant/housing basics.)*

\---

## 2\. High-Level System Architecture

```
                         ┌────────────────────────┐
                         │      Data Sources        │
                         │ (Gov portals, data.gov.in,│
                         │  news, community forums)  │
                         └────────────┬──────────────┘
                                      │
                         ┌────────────▼──────────────┐
                         │   Scraper / Ingestion Layer │
                         │  (requests+BS4 / Playwright,│
                         │   scheduled via APScheduler)│
                         └────────────┬──────────────┘
                                      │  raw HTML/text + metadata
                         ┌────────────▼──────────────┐
                         │  Preprocessing \\\\\\\& Chunking   │
                         │  (clean, chunk, tag: source, │
                         │   category, scrape\\\\\\\_date)     │
                         └────────────┬──────────────┘
                                      │
                         ┌────────────▼──────────────┐
                         │     Embedding + Vector DB     │
                         │  (sentence-transformers →      │
                         │        ChromaDB)                │
                         └────────────┬──────────────┘
                                      │
        ┌─────────────────────────────▼─────────────────────────────┐
        │                    FastAPI Backend                          │
        │                                                              │
        │   POST /query ──────► LangGraph Agent Pipeline               │
        │                                                              │
        │   ┌─────────────┐   ┌───────────────┐   ┌────────────────┐ │
        │   │ Intent Agent │──►│ Retrieval Agent│──►│ Verifier Agent │ │
        │   └─────────────┘   └───────────────┘   └───────┬────────┘ │
        │                                                    │loop if │
        │                                          stale/conflicting  │
        │                                                    ▼        │
        │                                          ┌────────────────┐ │
        │                                          │ Localizer Agent│ │
        │                                          └───────┬────────┘ │
        │                                                    ▼        │
        │                                            Final Response    │
        │                                    (answer + sources +       │
        │                                     "last verified" date)    │
        └──────────────────────────────────┬─────────────────────────┘
                                            │
                         ┌───────────────────▼───────────────────┐
                         │   LLM Fallback Router (reused module)   │
                         │  OpenRouter free → HF Inference → Ollama│
                         └───────────────────────────────────────┘
                                            │
                         ┌───────────────────▼───────────────────┐
                         │        Frontend (React/TS chat UI       │
                         │         or Streamlit for MVP)            │
                         └───────────────────────────────────────┘
```

\---

## 3\. Data Collection Sources

### A. Primary (official government) sources

|Source|What to collect|Category|
|-|-|-|
|FRRO / Bureau of Immigration (boi.gov.in)|Foreigner registration rules, required documents, visa extension process|Visa/Registration|
|Uttarakhand Tourism Development Board (uttarakhandtourism.gov.in)|Rishikesh-specific permits, tourist advisories|Visa/Tourism|
|Uttarakhand Transport Department|Bus routes, pass rules, fare info|Transport|
|Dehradun District Administration portal|Rishikesh sub-division civic notices (Rishikesh falls under Dehradun district)|General/Cross-cutting|
|e-District Uttarakhand portal|Certificates, registrations, aggregated citizen services|Multiple|
|Nagar Palika Parishad Rishikesh (municipal council)|Local notices, municipal services|General|
|National Health Mission Uttarakhand|Healthcare facility info (Phase 2)|Healthcare|

### B. Structured open data (check before scraping — cheaper than scraping)

* **data.gov.in** — search "Uttarakhand" for pre-structured datasets (healthcare facilities, transport routes, demographic data)

### C. Secondary / cross-reference sources (not primary — used by Verifier Agent to catch practical gaps)

* Local news: Amar Ujala / Times of India Dehradun edition (for recent rule changes)
* Expat/yoga-community forums, r/india (informal "how it actually works" info — always flagged as secondary/unofficial in the UI)

### D. Data collection rules

* Check and respect `robots.txt` on every site before scraping
* Low request rate, delays between requests — don't hammer government servers
* Store per-chunk metadata: `source\\\\\\\_url`, `scrape\\\\\\\_date`, `category`, `source\\\\\\\_tier` (official / secondary)
* No redistribution of full-text content — summarize/RAG, always link back to source
* Never present secondary-source info as official — Verifier Agent must flag tier

\---

## 4\. Phases of the Project

### Phase 0 — Setup \& Scoping (2-3 days)

* Finalize 2 MVP categories (visa/FRRO + transport)
* Set up repo structure, FastAPI skeleton, Chroma instance
* Identify and shortlist 10-15 target URLs

### Phase 1 — Data Pipeline (3-5 days)

* Write scraper (requests/BS4, Playwright if needed)
* Build preprocessing/chunking script with metadata tagging
* Generate embeddings, load into ChromaDB
* Manually verify retrieval quality on 5-10 sample queries

### Phase 2 — Core Agent Pipeline (4-6 days)

* Build LangGraph graph: Intent → Retrieval → Localizer (skip Verifier loop initially)
* Wire in LLM fallback router (OpenRouter → HF → Ollama, reused from earlier project)
* Expose `/query` endpoint via FastAPI
* Test end-to-end with real Rishikesh queries

### Phase 3 — Verifier Agent \& Trust Layer (3-4 days)

* Add Verifier Agent: detect stale (>N months old) or conflicting sources
* Implement conditional loop-back to Retrieval on failure
* Add "last verified: X days ago" + source-tier badges to responses

### Phase 4 — Frontend \& Polish (3-5 days)

* Build simple chat UI (React/TS or Streamlit)
* Add category selector, source citations, disclaimers
* Add `/admin/rescrape` and `/health` (data freshness dashboard)

### Phase 5 — Expansion (optional, post-MVP)

* Add healthcare + tenant/housing categories
* Add multi-language localization (Hindi, common tourist languages)
* Schedule automatic weekly re-scraping via APScheduler/cron

\---

## 5\. Tech Stack Summary

|Layer|Tool|
|-|-|
|Backend|FastAPI|
|Agent orchestration|LangGraph|
|Vector DB|ChromaDB|
|Embeddings|sentence-transformers (local, free)|
|LLM calls|OpenRouter free tier → HF Inference Providers → local Ollama (fallback router)|
|Scraper|requests + BeautifulSoup (Playwright if JS-rendered)|
|Scheduling|APScheduler / cron|
|Frontend|React + TypeScript (or Streamlit for MVP speed)|
|DB (metadata/logs)|SQLite / Postgres|

\---

## 6\. Key Disclaimers to Bake Into the Product

* Not legal/immigration advice — always link to official source for final action
* Clearly label secondary/community sources as unofficial
* Show data freshness ("last verified") on every answer

