# UE5 Modular Interaction Framework (C++ / Blueprint)

## Overview
This repository contains a modular object interaction framework developed in Unreal Engine 5 using C++ with Blueprint integration. The system was originally created for a **restaurant-focused commercial VR training simulation**, but was designed to support reusable interaction logic across multiple simulation scenarios.

The framework is built around a base **Grabbable** actor and extended using the **Decorator design pattern** to support runtime composition of object behaviors such as slicing, cooking, and stacking.

A key feature of this system is a **procedural mesh slicing system**, which allows objects to be cut into multiple pieces at runtime while maintaining physics interaction and compatibility with other gameplay systems.

> **Note:** Portions of this system were developed as part of a commercial VR training platform. Some implementation details cannot be publicly released. This repository focuses on system architecture, design patterns, documentation, and representative source code demonstrating the core interaction framework.

---

## Features
- Physics-based grab and release system  
- Highlight system using custom depth stencil  
- Support for static, skeletal, and procedural meshes  
- Modular behavior extension via Decorator pattern  
- Procedural mesh slicing at runtime  
- Dynamic material system for cooking state changes  
- Stackable object interaction system  
- Blueprint-exposed C++ classes for designer workflows  
- Event-driven architecture using Unreal delegates  

---

## Technical Highlights
This project demonstrates several software engineering and real-time simulation concepts:

- Object-Oriented Programming (OOP) in Unreal Engine C++
- Decorator design pattern for modular runtime behavior composition
- Blueprint ↔ C++ integration for hybrid designer/programmer workflows
- Procedural mesh generation and runtime mesh modification
- Physics-based VR interaction systems
- Event-driven architecture using delegates
- Dynamic material instance management for object state changes
- Reusable interaction systems across multiple simulation environments

---

## System Architecture

| Class | Responsibility |
|------|----------------|
| Grabbable | Base interaction logic |
| Decorator | Base decorator class |
| StackableDecorator | Enables stacking |
| SliceableDecorator | Enables procedural slicing |
| CookableDecorator | Enables cooking and material state changes |

This architecture allows a single object to support multiple behaviors simultaneously (e.g., sliceable and cookable) while maintaining a clean and reusable codebase.

For a detailed explanation of the architecture and design decisions, see:  
**Docs/Architecture_Explanation.md**

---

## Technologies Used
- Unreal Engine 5  
- C++  
- Blueprint Visual Scripting  
- Procedural Mesh Component  
- Gameplay Tags  
- Dynamic Material Instances  
- VR Interaction Systems  

---

## Video Demonstration
*(Insert slicing and cooking video here)*

---

## Design Goals
- Reusable interaction logic across multiple simulation modules  
- Modular object behaviors (sliceable, cookable, stackable)  
- Designer-friendly Blueprint integration  
- Support for VR physics interaction  
- Maintainable and extensible architecture
- Seamless navigation between Blueprint and C++ classes

---

## About
This interaction framework was originally developed as part of a commercial VR training platform and was designed to support reusable interaction systems across multiple simulation environments, including food preparation, lab work, and equipment training scenarios.

The repository is presented as a **technical case study** demonstrating system architecture, object-oriented design, Unreal Engine C++ development, and Blueprint integration for interactive simulation systems.

---

## Additional Technical Documentation

Additional documentation describing Blueprint and C++ integration workflows used in this system can be found in:

**Docs/Blueprint_Cpp_Workflows/**
