# Architecture Explanation – UE5 Modular Interaction Framework

## Overview

This document describes the architecture and design decisions behind the Modular Interaction Framework developed in Unreal Engine 5 using C++ and Blueprint integration. The system was originally designed for a restaurant-focused VR training simulation, but the architecture was intentionally built to support reuse across multiple simulation scenarios.

The core challenge addressed by this framework was that many objects in the simulation shared the same base interaction (grabbing), but required different combinations of additional behaviors such as slicing, cooking, and stacking. The system therefore needed to be modular, extensible, and maintainable.

---

## Design Goals

The architecture was designed with the following goals:

- Reusable interaction logic across multiple simulation modules
- Support for multiple object behaviors (sliceable, cookable, stackable)
- Compatibility with VR physics-based interaction
- Designer-friendly workflow through Blueprint integration
- Maintainable and extensible code architecture
- Avoid large and rigid class hierarchies
- Allow runtime composition of object behaviors
- Support runtime geometry modification (slicing)

---

## Core Architecture

The framework is built around a base **Grabbable** class that defines core interaction behavior for all interactive objects.

### Grabbable (Base Class)

The Grabbable class is responsible for:

- Physics-based grabbing and releasing
- Highlighting objects using custom depth stencil
- Supporting static meshes, skeletal meshes, and procedural meshes
- Broadcasting grab and release events using delegates
- Providing virtual functions for interaction behaviors (e.g., `Cook()`, `Slice()`)

All interactive objects in the simulation inherit from or contain a Grabbable component, ensuring consistent interaction behavior across the system.

---

## Why the Decorator Pattern Was Used

Many objects in the simulation share the same base interaction (grabbable), but only some objects require additional behaviors such as slicing, cooking, or stacking.

A naive inheritance-based approach would require creating separate classes for every combination of behaviors, such as:

- SliceableGrabbable
- CookableGrabbable
- StackableGrabbable
- SliceableCookableGrabbable
- SliceableStackableCookableGrabbable

This approach does not scale and quickly becomes difficult to maintain.

To solve this problem, the system uses the **Decorator design pattern**, which allows behaviors to be added modularly to an object without modifying the base class or creating many subclasses.

### Decorators Implemented

| Decorator | Responsibility |
|-----------|----------------|
| StackableDecorator | Enables objects to be stacked |
| SliceableDecorator | Enables procedural mesh slicing |
| CookableDecorator | Enables cooking state and material changes |

Decorators attach to a Grabbable object and extend its behavior. Multiple decorators can be applied to the same object, allowing a single object to be sliceable, cookable, and stackable simultaneously.

This approach keeps the code modular, reusable, and easier to extend with new behaviors in the future.

---

## Procedural Mesh Slicing System

One of the more technically complex systems in the framework is the **procedural mesh slicing system**, implemented in the SliceableDecorator.

### Why Procedural Meshes Were Used

Pre-cut meshes were not a viable solution because:

- Objects needed to be cut at arbitrary angles
- Users could slice objects multiple times
- Each slice needed to produce physically independent pieces
- The system needed to work across many different object types
- Storing many pre-cut mesh variants would not scale

Because of these constraints, meshes were converted from **Static Mesh → Procedural Mesh** at runtime, allowing geometry to be modified dynamically.

### Slicing Process Overview

When an object is sliced:

1. The static mesh is converted into a procedural mesh.
2. A slicing plane is calculated based on the cutting tool position and orientation.
3. The mesh is split into two halves along the slicing plane.
4. New cap geometry is generated to close the open faces created by the slice.
5. A new actor is spawned for the sliced-off portion.
6. Physics simulation is enabled for both resulting pieces.
7. The number of slices is tracked to prevent infinite subdivision and performance issues.

This system allowed realistic food preparation interactions in VR training scenarios.

---

## Blueprint and C++ Integration

The system was designed to support a **hybrid C++ / Blueprint workflow**.

The general approach was:

- Core interaction systems were implemented in C++ for performance and maintainability.
- Blueprint subclasses were used to configure meshes, materials, and interaction parameters.
- Events such as grab and release were exposed to Blueprint using delegates.
- C++ functions were exposed to Blueprint to allow designers to trigger behaviors such as cooking or slicing.
- Designers could create new interactive objects without modifying C++ code by combining Blueprint subclasses with decorators.

This workflow allowed engineers to maintain core systems while enabling designers to build and configure simulation content.

---

## Event-Driven Architecture

The interaction system uses an **event-driven architecture** to communicate between systems.

Examples of events include:

- Grab events
- Release events
- Slice events
- Cook state changes
- Stack events

These events are broadcast using Unreal Engine delegates. Other systems (such as audio, UI, scoring systems, or gameplay logic) can subscribe to these events and respond accordingly.

This approach reduces tight coupling between systems and makes the interaction framework easier to extend and maintain.

---

## Summary

The Modular Interaction Framework was designed to solve a common problem in simulation development: many objects share the same base interactions but require different combinations of additional behaviors.

The key architectural decisions were:

- Use a **Grabbable base class** for shared interaction behavior
- Use the **Decorator pattern** to add behaviors modularly
- Use **procedural meshes** for runtime geometry modification
- Use **Blueprint integration** for designer-friendly workflows
- Use an **event-driven architecture** to keep systems decoupled

This architecture allowed the interaction system to be reused across multiple VR training simulations while remaining maintainable and scalable.

---

## Tradeoffs and Limitations

Some tradeoffs and limitations of this architecture include:

- Procedural mesh slicing is more computationally expensive than using pre-cut meshes.
- The decorator system adds some architectural complexity compared to a simple inheritance model.
- Physics stability must be carefully managed when spawning sliced objects.
- Runtime mesh generation requires careful handling of normals, UVs, and collision meshes.

Despite these tradeoffs, the flexibility and reusability of the system made this architecture appropriate for a simulation environment where many different object types required similar interaction behaviors.
