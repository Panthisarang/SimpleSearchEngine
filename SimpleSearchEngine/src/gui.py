import tkinter as tk
from tkinter import ttk
from concurrent.futures import ThreadPoolExecutor
import search_engine  # Import the C++ module

class SearchEngineApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Search Engine")

        # Create widgets
        self.search_entry = ttk.Entry(root, width=50)
        self.search_button = ttk.Button(root, text="Search", command=self.on_search_button_clicked)
        self.results_listbox = tk.Listbox(root, width=50, height=15)

        # Layout
        self.search_entry.pack(pady=10)
        self.search_button.pack(pady=5)
        self.results_listbox.pack(pady=10)

        # Index documents using multithreading
        self.documents = ["doc1.txt", "doc2.txt", "doc3.txt"]
        self.index = {}

        self.executor = ThreadPoolExecutor(max_workers=4)
        self.executor.submit(self.index_documents)

    def index_documents(self):
        search_engine.createIndex(self.documents, self.index)

    def on_search_button_clicked(self):
        query = self.search_entry.get()
        self.executor.submit(self.perform_search, query)

    def perform_search(self, query):
        results = search_engine.search(query, self.index, self.documents)
        self.display_results(results)

    def display_results(self, results):
        self.results_listbox.delete(0, tk.END)
        if not results:
            self.results_listbox.insert(tk.END, "No documents found.")
        else:
            for docId in results:
                self.results_listbox.insert(tk.END, f"doc{docId + 1}")

if __name__ == "__main__":
    root = tk.Tk()
    app = SearchEngineApp(root)
    root.mainloop()
