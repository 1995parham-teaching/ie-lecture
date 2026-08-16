# Lecture 6 — JSON, Thrift and gRPC

69 slides, 6 vertical stacks. Topics (TOC indices): `0` Introduction ·
`1` Documentation & Validation · `2` Processing (using JavaScript) ·
`3` Thrift & gRPC · `4` Conclusion.

Arc: JSON syntax → why it needs a schema → JSON Schema in depth (string,
numeric, object, array, `$id`, annotations) → a validator → a parser example →
Thrift (definition file, Python client, Java server, handler) → gRPC (service
definition, field numbers) → gRPC compared to JSON over REST.

Code samples span **seven languages**: go, java, javascript, json, protobuf,
python, thrift. Each one has to be valid in its own right.

## Facts worth not re-deriving

- The JSON Schema example **is valid**. Its indentation looks wrong on the
  slide, which invites a "fix" — it was parsed and confirmed correct. Leave it.
- "Semantics", not "Symantec" — that typo was in the deck.
- The instructor attribution is **Parham Alvani**.
- Protobuf **field numbers** are the wire identity: renaming a field is safe,
  renumbering it is not. That is the point of the field-numbers slide.

## Cautions

- Any JSON or JSON Schema you add must be run through a parser before it goes on
  a slide — this deck is specifically about schema validity.
- `diag/reference-based-validation.drawio` is the source for the validation
  diagram.
