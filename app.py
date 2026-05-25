from flask import Flask, render_template, request, jsonify
from werkzeug.utils import secure_filename
import os
import pdfplumber
from transformers import pipeline

app = Flask(__name__, template_folder='templates', static_folder='static')
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Load ML pipelines
classifier = pipeline("zero-shot-classification", model="facebook/bart-large-mnli")
summarizer = pipeline("summarization", model="facebook/bart-large-cnn")
clause_labels = ["Confidentiality", "Termination", "Payment Terms", "Risk Clause", "Obligations"]

@app.route('/')
def home():
    return render_template("index.html")

@app.route('/upload', methods=['POST'])
def upload_file():
    uploaded_file = request.files['file']
    if uploaded_file.filename != '':
        filename = secure_filename(uploaded_file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        uploaded_file.save(filepath)

        # Extract text from PDF
        with pdfplumber.open(filepath) as pdf:
            text = ''
            for page in pdf.pages:
                extracted = page.extract_text()
                if extracted:
                    text += extracted + '\n'

        if not text.strip():
            return jsonify({"status": "error", "message": "No extractable text."})

        # Classification
        sentences = text.split(". ")
        classified = []
        for sentence in sentences[:10]:
            result = classifier(sentence, candidate_labels=clause_labels)
            classified.append({
                "clause": sentence.strip(),
                "type": result['labels'][0]
            })

        # Summarization
        summary_input = text[:1000]
        summary = summarizer(summary_input, max_length=100, min_length=30, do_sample=False)[0]['summary_text']

        return jsonify({
            "status": "success",
            "summary": summary,
            "classified_clauses": classified
        })

    return jsonify({"status": "error", "message": "No file uploaded"})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=7860)
