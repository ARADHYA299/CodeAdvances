from sentence_transformers import SentenceTransformer
import os
import re
import numpy as np
from vector_store.faiss_index import FaissIndex

class Embedder:

    def __init__(self):
        
        self.model = SentenceTransformer("all-MiniLM-L6-v2")

    def clean_text(self, text):
        text = text.lower()

        # remove emails
        text = re.sub(r'\S+@\S+', '', text)

        # remove urls
        text = re.sub(r'http\S+', '', text)

        # remove special characters
        text = re.sub(r'[^a-zA-Z0-9\s]', ' ', text)

        # remove extra spaces
        text = re.sub(r'\s+', ' ', text).strip()

        return text

    def load_dataset(self):
        dataset_path = "data/20_newsgroups"

        print("Dataset path:", os.path.abspath(dataset_path))
        print("Exists:", os.path.exists(dataset_path))

        if not os.path.exists(dataset_path):
            raise ValueError("Dataset folder not found.")

        documents = []
        labels = []

        # Walk through all folders and files
        for root, dirs, files in os.walk(dataset_path):

            label = os.path.basename(root)

            for file in files:
                file_path = os.path.join(root, file)

                try:
                    with open(file_path, "r", encoding="latin-1") as f:
                        text = f.read()

                    text = self.clean_text(text)

                    if len(text) > 0:
                        documents.append(text)
                        labels.append(label)

                except Exception as e:
                    print("Skipping file:", file_path)

        return documents, labels

    def create_embeddings(self, texts):

        embeddings = self.model.encode(
            texts,
            show_progress_bar=True,
            convert_to_numpy=True,
            batch_size=32
        )

        return embeddings


if __name__ == "__main__":

    embedder = Embedder()

    print("Loading dataset...")

    texts, labels = embedder.load_dataset()

    print("Documents loaded:", len(texts))

    if len(texts) == 0:
        print("No documents found. Check dataset structure.")
        exit()

    print("Generating embeddings...")

    embeddings = embedder.create_embeddings(texts)

    print("Embeddings generated:", embeddings.shape)
    np.save("data/embeddings.npy", embeddings)
    np.save("data/labels.npy", labels)

    print("Embeddings and labels saved.")
    
    dimension = embeddings.shape[1]
    
    index = FaissIndex(dimension)
    
    print("Building Faiss index...")
    index.build(embeddings)
    
    index.save("data/news_index.faiss")

