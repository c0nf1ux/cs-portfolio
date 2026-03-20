# CRUD Module for Austin Animal Center Database
# Provides Create, Read, Update, and Delete functionality for MongoDB operations

from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
    """CRUD operations for Animal collection in MongoDB"""
    
    def __init__(self, username, password):
    # Takes username and password as parameters
        USER = username
        PASS = password  
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
    
    def update(self, query, data):
        """
        Update document(s) in animals collection
        
        Args:
            query (dict): Key/value pairs to identify documents to update
            data (dict): Key/value pairs of fields to update using MongoDB $set operator
            
        Returns:
            int: Number of documents modified
        """
        try:
            if query is not None and data is not None:
                # Use update_many to update all matching documents
                result = self.collection.update_many(query, {"$set": data})
                modified_count = result.modified_count
                print(f"Documents updated: {modified_count}")
                return modified_count
            else:
                print("Query or update data is empty")
                return 0
        except Exception as e:
            print(f"Update operation failed: {e}")
            return 0
    
    def delete(self, query):
        """
        Delete document(s) from animals collection
        
        Args:
            query (dict): Key/value pairs to identify documents to delete
            
        Returns:
            int: Number of documents deleted
        """
        try:
            if query is not None:
                # Use delete_many to delete all matching documents
                result = self.collection.delete_many(query)
                deleted_count = result.deleted_count
                print(f"Documents deleted: {deleted_count}")
                return deleted_count
            else:
                print("Query is empty")
                return 0
        except Exception as e:
            print(f"Delete operation failed: {e}")
            return 0