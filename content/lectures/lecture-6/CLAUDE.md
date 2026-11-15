# Lecture 6 — JSON, Thrift and gRPC

61 slides, 6 vertical stacks. Topics (TOC indices): `0` Introduction ·
`1` Documentation & Validation · `2` Processing (using JavaScript) ·
`3` Thrift & gRPC · `4` Conclusion.

Arc: JSON syntax → why it needs a schema → JSON Schema (one keyword table,
objects in depth, a schema for the Course, a real validator run) → a parser example →
Thrift (definition file, Python client, Java server, handler, the stack, the
wire) → gRPC (service definition, field numbers, protobuf on the wire, one call
over HTTP/2, the four kinds of RPC) → gRPC compared to JSON over REST.

Code samples span **seven languages**: go, java, javascript, json, protobuf,
python, thrift. Each one has to be valid in its own right.

## Facts worth not re-deriving

- The JSON Schema stack (`#/15`) was cut from 20 slides to 7 on 2026-11-15:
  the user found the keyword-by-keyword slides "too much". The keywords are one
  table now; do not bring back a slide per keyword. The Product example was
  replaced by a schema for the deck's own Course (`#/5/2`).
- Every schema result on `#/15/3`–`#/15/5` is a real run of Python
  `jsonschema` 4.26.0 (`Draft202012Validator`, Python 3.11): the four address
  instances (each also run without `additionalProperties: false` — only the
  `city` row changes), the `#/5/2` Course passing the Course schema, and the
  rejected Course's four errors in `iter_errors` order. The output on `#/15/5`
  comes from exactly the two Python lines on that slide. If you change the
  schema or an instance, re-run it.
- `format` is an annotation by default in 2020-12: `"not-an-email"` passes
  `{"format": "email"}` unless a format checker is passed (checked).
- "Semantics", not "Symantec" — that typo was in the deck.
- The instructor attribution is **Parham Alvani**.
- Protobuf **field numbers** are the wire identity: renaming a field is safe,
  renumbering it is not. That is the point of the field-numbers slide.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                             | Slide                                          |
| -------------------------------- | ---------------------------------------------- |
| `thrift-stack.svg`               | The Stack — after Java Handler                 |
| `thrift-wire.svg`                | On the Wire — `add(1, 1)`, binary vs compact   |
| `protobuf-wire.svg`              | gRPC stack: On the Wire — after Field Numbers  |
| `grpc-http2.svg`                 | gRPC stack: One Call over HTTP/2               |
| `grpc-streaming.svg`             | gRPC stack: Four Kinds of RPC                  |
| `reference-based-validation.svg` | Parser, then Validator — after How to Validate |

- `protobuf-wire.svg` bytes come from `protoc --encode=course.Course` on the
  Service Definition `.proto`, with the same values as the Introduction
  example; `protoc --decode_raw` gives the field split. The size bars are
  measured: protobuf 48 B, CBOR 99 B (`cbor2.dumps`, and the same bytes as the
  CBOR slide), minified JSON 126 B. If the example data changes, re-encode.
- `grpc-http2.svg` is a real capture: a grpc-go 1.84 server and client for that
  `.proto` with a tee on the server's `net.Conn`, frames decoded with
  `x/net/http2.Framer` and `hpack`. `:authority` and `user-agent` were left
  out; the DATA bytes are exact (5-byte prefix + the 48-byte Course).
- `grpc-streaming.svg` method names (`ListStudents`, `Enroll`, `Watch`) are not
  in the Service Definition slide. They were compiled with `protoc` and each
  kind was run once in grpc-go, so the signatures are valid if added.
- `thrift-wire.svg` bytes come from Thrift 0.25 Python (`send_add(1, 1)` into a
  `TMemoryBuffer`) for `TBinaryProtocol` (30 B) and `TCompactProtocol` (12 B).
  A full `ping()`/`add()` round trip over `TSocket`/`TSimpleServer` was also
  run. The seqid is 0 because the Python client does not count it up.
- `thrift-stack.svg` uses the class names on the Python Client and Java Server
  slides. The server's `TBinaryProtocol` is not in that code: it is the default
  protocol of `TSimpleServer.Args`. Layer names follow
  thrift.apache.org/docs/concepts (Server, Processor, Protocol, Transport).
- `reference-based-validation.svg` replaced the draw.io
  `reference-based-validation.png` (source `diag/` removed). The old drawing put
  the validator before the parser; a JSON Schema validator works on parsed
  values, so the parser comes first. "Reference-based" means validation
  against a reference document (the schema), not `$ref`. The schema and the
  three inputs were run through Ajv 8.20 (`Ajv2020`, `strict: true`, schema
  text extracted from the SVG) after `JSON.parse` in Node 20: the valid one
  passes, `{id: 9531024}` throws `SyntaxError: Expected property name or '}'
in JSON at position 1`, `{"name": "Ali"}` gives `must have required
property 'id'`. Node's message wording changes between versions; re-capture
  if you change the input.
- `thrift-efficiency.png` is a chart from an external source and
  `thrift.png` is a logo; both are untouched.

## Java Server compiles

The Java Server slide used to start a `secure` runnable it never defined, and
used `handler`/`processor` as undeclared fields. It is now a whole
`JavaServer` class with the TLS server removed (it needs a keystore and does not
fit the slide). The `TThreadPoolServer` comment was dropped too: with it the
block was 25 lines and clipped. Verified with Thrift 0.25: the deck's Thrift definition plus the
upstream `shared.thrift` through `thrift -r --gen java`, then `javac -Xlint:all`
in `eclipse-temurin:21-jdk` against `libthrift-0.25.0`, `slf4j-api` and
`javax.annotation-api` (no warnings in the slide code), together with the Java
Handler slide (imports added). A Thrift 0.25 Python client did `ping()` and
`add(1, 1)` = 2 against it. Imports are left off the slide, as on the Handler
slide. The deck's `.thrift` has no `namespace java`, so the generated classes
are in the default package. Escape the generics (`&lt;&gt;`) in the HTML —
an unescaped `<CalculatorHandler>` breaks Prettier's go-template parser.

## Introduction slides

The CBOR and positional slides have `<h2>` titles ("The Same Course in CBOR",
"The Same Course, Positional"); the positional one has a one-line caption on
the field order. The CBOR dump puts each text header and its bytes on one line
(16 lines, was 26 and clipped). The bytes are unchanged: the hex was joined and
checked with `cbor2` — 99 B, equal to `cbor2.dumps` of the JSON example and
decodes back to it.

## What is Next?!

Lists only what the deck does not cover: YAML, MessagePack, Apache Avro,
FlatBuffers / Cap'n Proto. Protobuf and Thrift were removed from it because the
deck teaches both. If you add a section on one of these, remove it here.

## Cautions

- Any JSON or JSON Schema you add must be run through a parser before it goes on
  a slide — this deck is specifically about schema validity.
