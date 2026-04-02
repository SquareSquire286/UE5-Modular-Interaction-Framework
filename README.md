# UE5 Modular Interaction Framework (C++ / Blueprint)

## Overview
This repository contains a modular object interaction framework developed in Unreal Engine 5 using C++ with Blueprint integration. The system was originally created for a **restaurant-focused commercial VR training simulation**, but was designed to support reusable interaction logic across multiple simulation scenarios.

The framework is built around a base **Grabbable** actor and extended using the **Decorator design pattern** to support runtime composition of object behaviors such as slicing, cooking, and stacking.

A key feature of this system is a **procedural mesh slicing system**, which allows objects to be cut into multiple pieces at runtime while maintaining physics interaction and compatibility with other gameplay systems.

> **Note:** Portions of this system were developed as part of a commercial VR training platform. Some implementation details CANNOT be publicly released. This repository focuses on system architecture, design patterns, documentation, and representative source code demonstrating the core interaction framework.

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

## System Architecture

The system is built around a base **Grabbable** class that defines core interaction behavior. Additional functionality is added through decorator classes that extend behavior without duplicating logic.

| Class | Responsibility |
|------|----------------|
| Grabbable | Base interaction logic |
| Decorator | Base decorator class |
| StackableDecorator | Enables stacking |
| SliceableDecorator | Enables procedural slicing |
| CookableDecorator | Enables cooking and material state changes |

This architecture allows a single object to support multiple behaviors simultaneously (e.g., sliceable and cookable) while maintaining a clean and reusable codebase.

The Decorator pattern was chosen to avoid large class hierarchies and to allow object behaviors to be composed modularly at runtime.

---

## Procedural Mesh Slicing

The slicing system works as follows:

1. Converts static meshes to procedural meshes at runtime  
2. Defines a slicing plane based on the cutting tool position and orientation  
3. Splits the procedural mesh into two halves along the slicing plane  
4. Generates cap geometry to close open mesh surfaces created by the slice  
5. Spawns a new actor for the sliced portion  
6. Applies physics to both resulting pieces  
7. Tracks slice count to prevent infinite subdivision  

This system was used in a VR cooking simulation to allow users to prepare food items through realistic interaction.

---

## Blueprint Integration

All core classes are implemented in C++ and exposed to Blueprint, allowing designers to:

- Create Blueprint subclasses of interaction objects  
- Hook into grab/release events  
- Configure meshes and materials  
- Adjust slicing and cooking parameters without modifying C++ code  

This hybrid C++/Blueprint workflow was used in production VR training simulations.

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

## Repository Structure
ue5-modular-interaction-framework/
│
├── README.md
├── Docs/
│ ├── Stackable_Component.pdf
│ ├── Sliceable_Component.pdf
│ ├── UML_Diagram.png
│ ├── Architecture_Explanation.md
│
├── Source_Examples/
│ ├── Grabbable.h
│ ├── Grabbable.cpp
│ ├── CookableDecorator.h
│ ├── CookableDecorator.cpp
│
├── Media/
│ ├── slicing_demo.mp4
│ ├── cooking_demo.mp4
---

---

## Video Demonstration
*(Insert slicing and cooking video here)*

Suggested clips:
- Procedural mesh slicing
- Cooking state change on grill
- Physics-based grabbing interaction

---

## Design Goals

This system was designed with the following goals:

- Reusable interaction logic across multiple simulation modules  
- Modular object behaviors (sliceable, cookable, stackable)  
- Designer-friendly Blueprint integration  
- Support for VR physics interaction  
- Maintainable and extensible architecture  

---

## About

This interaction framework was originally developed as part of a commercial VR training platform and was designed to support reusable interaction systems across multiple simulation environments, including food preparation, lab work, and equipment training scenarios.

The repository is presented as a **technical case study** demonstrating system architecture, object-oriented design, Unreal Engine C++ development, and Blueprint integration for interactive simulation systems.
