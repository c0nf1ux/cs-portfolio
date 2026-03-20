# CRUD Module for Austin Animal Center Database
# Provides Create and Read functionality for MongoDB operations

from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
    """CRUD operations for Animal collection in MongoDB"""
    
    def __init__(self):
        """
        Initialize connection to MongoDB with authentication
        Hardwired to use aac database, animals collection, and aacuser
        """
        # Connection Variables
        USER = 'aacuser'
        PASS = 'MySecurePassword123'  
        HOST = 'localhost'
        PORT = 27017
        DB = 'aac'
        COL = 'animals'
        
        # Initialize Connection
        self.client = MongoClient('mongodb://%s:%s@%s:%d' % (USER, PASS, HOST, PORT))
        self.database = self.client['%s' % (DB)]
        self.collection = self.database['%s' % (COL)]
    
    def create(self, data):
        """
        Insert a new document into animals collection
        
        Args:
            data (dict): Document with key/value pairs to insert
            
        Returns:
            bool: True if insert successful, False otherwise
        """
        try:
            if data is not None:
                self.database.animals.insert_one(data)  # data should be dictionary
                return True
            else:
                raise Exception("Nothing to save, because data parameter is empty")
        except Exception as e:
            print(f"Create operation failed: {e}")
            return False
    
    def read(self, query):
        """
        Query documents from animals collection
        
        Args:
            query (dict): Key/value pairs to search for
            
        Returns:
            list: List of matching documents, empty list if none found
        """
        try:
            if query is not None:
                # Use find() cursor and convert to list
                cursor = self.collection.find(query)
                results = list(cursor)
                return results
            else:
                print("Query parameter is empty")
                return []
        except Exception as e:
            print(f"Read operation failed: {e}")
            return []
