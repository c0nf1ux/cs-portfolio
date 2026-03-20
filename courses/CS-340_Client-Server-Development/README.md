# CS-340: Client Server Development

## Course Overview

**Course:** CS-340: Client Server Development
**Institution:** Southern New Hampshire University (SNHU)
**Semester:** Early 2025
**Focus:** Full-stack development with NoSQL databases, Python, and interactive data visualization

This course provides comprehensive training in client-server architecture, database design and management, and building interactive web applications. Students learn to design and implement complete solutions that connect backend databases with frontend user interfaces.

---

## Course Description

CS-340 is a comprehensive course in client-server development that covers the complete workflow of building data-driven applications. The curriculum emphasizes practical implementation of full-stack solutions using modern technologies including NoSQL databases, Python backend development, and web-based interactive dashboards. Students gain hands-on experience with real-world datasets and develop solutions that demonstrate both technical proficiency and professional development practices.

---

## Key Topics Covered

### Database Technologies
- **MongoDB**: NoSQL database design and implementation
- **CRUD Operations**: Create, Read, Update, Delete operations with MongoDB
- **Database Indexing**: Performance optimization through strategic indexing
- **Authentication & Security**: User authentication, password management, and secure database connections
- **Query Optimization**: Writing efficient queries and using aggregation pipelines

### Backend Development
- **Python**: Primary language for backend services
- **PyMongo**: Python MongoDB driver for database connectivity
- **Connection Management**: Establishing secure connections with credentials and authentication
- **Data Validation**: Ensuring data integrity and proper error handling
- **Module Design**: Building reusable, well-structured CRUD modules

### Frontend & Visualization
- **Dash & Plotly**: Interactive web dashboard frameworks
- **Jupyter Notebooks**: Development environment and literate programming
- **Data Tables**: Interactive tables with filtering, sorting, and pagination
- **Geolocation Visualization**: Maps and spatial data representation
- **Chart Types**: Pie charts, bar graphs, and custom visualizations

### Professional Development
- **Documentation**: README files and technical documentation
- **Code Quality**: Clean code principles and best practices
- **Testing**: Validation of database operations and application functionality
- **Version Control**: Managing code repositories and project history

---

## Languages & Tools

### Programming Languages
- **Python 3**: Backend development and data processing
- **JavaScript/HTML/CSS**: Dashboard frontend components

### Databases & Data Management
- **MongoDB**: NoSQL document database
- **BSON**: Binary JSON format for MongoDB documents
- **PyMongo**: Python MongoDB driver

### Development Frameworks & Libraries
- **Dash**: Interactive web application framework (by Plotly)
- **Plotly**: Data visualization library
- **Pandas**: Data manipulation and analysis
- **Jupyter**: Interactive notebooks for development and documentation
- **Dash Leaflet**: Geographic mapping component

### Tools & Platforms
- **Jupyter Notebook (.ipynb)**: Interactive development and testing
- **Git**: Version control
- **Python Virtual Environments**: Dependency isolation

---

## Projects & Assignments

### Module 1-2: Introduction to MongoDB
**Topics:** MongoDB fundamentals, database setup, basic concepts
**Deliverables:** Conceptual understanding of NoSQL databases and MongoDB architecture

### Module 3: Database Indexing & Authentication
**Assignment:** 3-1 Database Indexing and Authentication
**Topics:**
- Creating and managing database indexes for performance
- Implementing user authentication and authorization
- Password management and secure connections
- Access control patterns

### Module 4: CRUD Python Module (Project 1)
**Project:** Austin Animal Center (AAC) CRUD Module
**Files:**
- `CRUD_Python_Module.py` - Primary implementation
- `CRUD_Python_Module (1).py` - Variant implementation
- `CRUD_Python_Module Project 1.py` - Project-specific version
- `ProjectOneTestScript.ipynb` - Test cases and validation

**Description:** Build a Python class (`AnimalShelter`) that provides Create and Read functionality for a MongoDB collection of animal shelter data. The module demonstrates:
- Secure MongoDB connection with authentication
- Insertion of new animal records
- Querying with single and multiple filter criteria
- Proper error handling and return values
- Work with real Austin Animal Center dataset (10,000+ records)

**Key Features:**
```python
class AnimalShelter:
    def create(data) -> bool      # Insert new document
    def read(query) -> list       # Query documents with filters
```

**Sample Dataset:**
- 10,003+ animal records
- Fields: name, age, breed, animal_type, outcome_type, location coordinates
- Real-world data with missing values and edge cases

### Module 5: Client-Side Authentication
**Assignment:** 5-2 Client-side Authentication
**Topics:**
- User login and session management
- Frontend authentication flows
- Secure credential handling in web applications
- Session tokens and authentication middleware

### Module 6: Grazioso Salvare Dashboard (Final Project)
**Project:** Interactive Animal Shelter Dashboard
**Files:**
- `ModuleSixMilestone.ipynb` - Project milestone and development
- `Project 2 Heath Davis/ProjectTwoDashboard.ipynb` - Enhanced dashboard with filters

**Description:** Develop an interactive Dash dashboard for Grazioso Salvare animal rescue organization. The dashboard enables:
- Real-time filtering of animal records by rescue type
- Interactive data tables with sorting and filtering
- Geolocation mapping of animal locations
- Data visualization with pie charts showing breed distribution
- Dynamic updates based on user selections

**Dashboard Features:**
1. **Rescue Type Filters:**
   - Water Rescue: Labrador Retrievers, Chesapeake Bay Retrievers, Newfoundlands (female, 26-156 weeks)
   - Mountain/Wilderness Rescue: German Shepherds, Huskies, Malamutes, etc. (male, 20-300 weeks)
   - Disaster/Individual Tracking: Dobermans, German Shepherds, Bloodhounds, etc. (male, 26-156 weeks)

2. **Interactive Components:**
   - Paginated data table (10 rows per page)
   - Single row selection with column highlighting
   - Real-time breed distribution pie chart
   - Clickable map markers with animal information
   - Reset option to view all records

3. **Data Visualization:**
   - Austin-centered map (coordinates: 30.75°N, 97.48°W)
   - Breed distribution pie charts
   - Location markers with popups
   - Professional Grazioso Salvare branding

**Technologies:**
- Jupyter Dash for interactive components
- Plotly for charting
- Dash Leaflet for mapping
- Pandas for data manipulation
- Dynamic callbacks for component interaction

---

## Project Structure

```
CS-340_Client-Server-Development/
├── README.md                                    # This file
├── CRUD_Python_Module.py                       # Main CRUD implementation
├── CRUD_Python_Module (1).py                   # Alternative version
├── CRUD_Python_Module Project 1.py             # Project-specific implementation
├── ProjectOneTestScript.ipynb                  # Module 4 test cases
├── ProjectOneTestScripts.ipynb                 # Additional tests
├── ModuleFourTestScript.ipynb                  # CRUD module testing
├── ModuleSixMilestone.ipynb                    # Dashboard milestone
├── ProjectTwoDashboard.html                    # Dashboard export
├── Project 2 Heath Davis/
│   ├── CRUD_Python_Module (2).py               # Final CRUD version
│   └── ProjectTwoDashboard.ipynb               # Enhanced dashboard
├── Grazioso_Salvare_Logo.png                   # Organization logo
├── Module 6 Heath Davis.zip                    # Project archive
├── Module 6 Heath Davis (1).zip                # Backup archive
└── [Documentation files - .docx]               # Assignment submissions
```

---

## Key Learning Outcomes

By completing this course, students will be able to:

1. **Database Design & Management**
   - Design and implement NoSQL MongoDB databases
   - Create effective indexes for performance optimization
   - Write efficient queries using various filter criteria
   - Implement authentication and access controls

2. **Backend Development**
   - Build reusable Python modules for database operations
   - Handle errors gracefully with proper exception management
   - Work with real-world datasets and edge cases
   - Design secure connections with proper credential management

3. **Frontend Development**
   - Create interactive web dashboards using Dash/Plotly
   - Implement data filtering and sorting user interfaces
   - Build geolocation visualizations
   - Design responsive data tables and charts

4. **Full-Stack Integration**
   - Connect frontend applications to backend databases
   - Implement callback-driven interactivity
   - Manage data flow between components
   - Deploy complete web applications

5. **Professional Development**
   - Write clear technical documentation
   - Test code thoroughly with automated scripts
   - Manage versions and project history
   - Present work professionally

---

## Technical Requirements

### Software Requirements
- Python 3.7 or higher
- MongoDB (local or remote instance)
- Jupyter Notebook or JupyterLab
- Web browser for dashboard access

### Python Libraries
```
pymongo>=3.11.0          # MongoDB driver
pandas>=1.0.0            # Data manipulation
dash>=2.0.0              # Interactive dashboards
plotly>=5.0.0            # Data visualization
dash-leaflet>=0.1.0      # Geographic mapping
```

### MongoDB Setup
- Database: `aac` (Austin Animal Center)
- Collection: `animals`
- User: `aacuser` with appropriate permissions
- Data: Animal shelter records with breed, outcome, location, and demographic data

---

## File Index

### Core Implementation Files
| File | Purpose | Key Content |
|------|---------|-------------|
| `CRUD_Python_Module.py` | Main CRUD class | AnimalShelter class with create/read methods |
| `CRUD_Python_Module (1).py` | CRUD variant | Alternative implementation approach |
| `CRUD_Python_Module Project 1.py` | Project version | Optimized for project requirements |

### Testing & Validation
| File | Purpose | Coverage |
|------|---------|----------|
| `ProjectOneTestScript.ipynb` | Project 1 validation | CRUD operations testing |
| `ProjectOneTestScripts.ipynb` | Extended tests | Edge cases and query validation |
| `ModuleFourTestScript.ipynb` | Module 4 tests | Create/Read operation verification |

### Dashboard & Visualization
| File | Purpose | Features |
|------|---------|----------|
| `ModuleSixMilestone.ipynb` | Initial dashboard | Basic filtering and mapping |
| `ProjectTwoDashboard.ipynb` | Final dashboard | Advanced filtering, charts, maps |
| `ProjectTwoDashboard.html` | Dashboard export | Static HTML version for sharing |

### Project Assets
| File | Purpose | Usage |
|------|---------|-------|
| `Grazioso_Salvare_Logo.png` | Organization branding | Dashboard header |
| `Module 6 Heath Davis.zip` | Project archive | Complete project backup |

### Documentation (Word Documents)
- `AAC Project One ReadMe Heath Davis.docx` - Project 1 documentation
- `Grazioso Salvare Animal Rescue ReadMe Heath Davis.docx` - Final project overview
- `4-1 Milestone Create and Read in Python Heath Davis.docx` - Milestone submission
- `5-2 Client-side Authentication Heath Davis.docx` - Authentication assignment
- `6-2 Project Draft Heath Davis.docx` - Final project draft

---

## Getting Started

### 1. Setup MongoDB
```bash
# Start MongoDB service
# Ensure aac database and animals collection exist
# Create aacuser with appropriate permissions
```

### 2. Install Dependencies
```bash
pip install pymongo pandas dash plotly dash-leaflet jupyter
```

### 3. Test CRUD Module
```bash
# Run test script to verify database connectivity
jupyter notebook ProjectOneTestScript.ipynb
```

### 4. Launch Dashboard
```bash
# Run the dashboard application
jupyter notebook ModuleSixMilestone.ipynb
# or
jupyter notebook "Project 2 Heath Davis/ProjectTwoDashboard.ipynb"
```

---

## Learning Progression

The course follows a structured progression from foundational to advanced concepts:

1. **Foundation (Modules 1-2)**: MongoDB basics and concepts
2. **Core CRUD (Module 4)**: Reading and writing data with Python
3. **Optimization (Module 3)**: Indexing and authentication for performance
4. **Security (Module 5)**: Client-side authentication patterns
5. **Integration (Module 6)**: Full-stack dashboard application

This progression ensures students build skills incrementally, with each module reinforcing previous concepts while introducing new complexity.

---

## Professional Development Notes

### Code Quality Observations
- Clear class structure with docstrings
- Proper exception handling in database operations
- Input validation before database writes
- Separation of concerns (CRUD module vs. Dashboard)

### Best Practices Demonstrated
- Hardcoded credentials are separated from production code (noted for improvement)
- Connection pooling through MongoDB client
- Reusable module design for multiple projects
- Comprehensive testing scripts

### Areas for Enhancement
- Move credentials to environment variables
- Add Update and Delete operations to complete CRUD
- Implement query builders for complex filters
- Add logging for debugging and monitoring

---

## Course Completion Summary

This course provides a comprehensive foundation in full-stack development with practical, real-world applications. Students complete multiple projects ranging from simple CRUD modules to complex interactive dashboards, demonstrating mastery of database design, backend programming, and frontend visualization techniques. The Austin Animal Center project provides an authentic context for learning with real datasets, while the Grazioso Salvare dashboard demonstrates professional-grade application development.

---

**Last Updated:** March 2026
**Author:** Heath Davis
**Course Level:** Intermediate to Advanced
**Credits:** 3 semester hours
