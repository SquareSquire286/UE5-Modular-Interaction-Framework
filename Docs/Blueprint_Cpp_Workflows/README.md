# Blueprint ↔ C++ Workflow Documentation

This folder contains technical documentation written during the development of the Modular Interaction Framework to support hybrid Blueprint and C++ workflows in Unreal Engine 5.

These documents were created to standardize communication between Blueprint systems and C++ systems and to document solutions to common Unreal Engine workflow challenges encountered during development.

## Documents

| Document | Description |
|---------|-------------|
| Blueprint_Cpp_Spawn_Parameters.pdf | Describes how to mimic overloaded constructors using SpawnActorDeferred and exposed parameters |
| Blueprint_Native_Event_Override.pdf | Describes how to override C++ functions as Blueprint events using BlueprintNativeEvent |
| Blueprint_From_Cpp_Class_Workflow.pdf | Describes the workflow for deriving Blueprint classes from C++ classes and common compilation issues |

These workflows were used extensively in the Modular Interaction Framework to enable a hybrid C++ / Blueprint architecture that allowed engineers to implement core systems in C++ while allowing designers to configure and extend behavior in Blueprint.
