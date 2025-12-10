---
applyTo: '**'
---


# 代码生成规则

## 核心原则 (Meta-Rules)
- **默认遵循社区标准**：除非下方有明确覆盖，否则默认遵循各语言的官方风格指南（如 Python PEP8, Java Google Style, Go Effective Go, C++ Core Guidelines）。
- **可读性 > 简洁性**：代码必须清晰表达意图，宁可长命名也不要模糊的缩写。
- **安全性优先**：默认生成安全的代码（防止注入、内存泄漏、缓冲区溢出）。

## 代码规范与风格

### 命名与格式
- **命名**：严禁单字母命名（循环变量 `i, j` 除外）。常量必须使用 `UPPER_SNAKE_CASE`。避免魔法值，必须提取为常量。
- **缩进**：统一使用**空格**（C/C++/Java/TS: 4空格; JS/JSON/YAML: 2空格; Go: Tab）。
- **导入顺序**：标准库 -> 第三方库 -> 本地模块（组间空一行）。

### 函数与类设计
- **单一职责**：函数行数尽量控制在 50 行以内，每个函数只做一件事。
- **参数限制**：参数超过 3 个时，请使用配置对象/结构体。
- **布尔参数**：禁止使用布尔标志参数（如 `print(true)`），使用枚举或拆分函数。
- **副作用**：纯函数优先。若有副作用（IO、修改全局状态），请在注释中注明。

## 语言特定约束 (Language Specifics)

### C/C++ (Modern C++17/20)
- **内存管理**：
  - **严禁裸指针**：除非对接 C 接口，否则必须使用智能指针 (`std::unique_ptr`, `std::shared_ptr`)。
  - **RAII**：严格遵循 RAII 原则管理资源，禁止手动 delete。
  - **字符串**：使用 `std::string` / `std::string_view`，禁止使用 C 风格字符串 (`char*`)。
- **头文件**：使用 `#pragma once` 替代传统的 include guard。
- **类型安全**：使用 `nullptr` 替代 `NULL`；使用 `enum class`；使用 `static_cast`。
- **安全性**：禁止 `strcpy`, `sprintf` 等不安全函数，使用 `snprintf` 或 fmt 库。

### Python
- **类型提示**：所有函数参数和返回值必须包含 Type Hints。
- **文档**：使用 Google Style Docstrings。
- **私有性**：内部函数使用 `_` 前缀。

### Go
- **错误处理**：显式处理 `err`，禁止使用 `_` 忽略错误。
- **风格**：严格遵循 `gofmt` 和 `goimports`。

### Java/C#
- **工具类**：使用 Lombok (Java) 减少样板代码（getter/setter/builder），除非项目明确禁止。
- **异常**：禁止捕获 `Exception` 基类，必须捕获具体异常。

## 错误处理与日志
- **异常处理**：
  - C++/Java/Py: 使用 try-catch，禁止吞掉异常（Empty Catch Block），必须记录或抛出。
  - Go/C: 必须检查返回值/错误码。
  - Rust: 使用 `Result/Option`，禁止 `unwrap()`。
- **日志**：
  - 使用结构化日志（Key-Value pairs）。
  - 级别：DEBUG (开发), INFO (关键流程), WARN (潜在问题), ERROR (操作失败)。
  - **严禁**在日志中记录敏感数据（密码、Token、PII）。

## 4. 文档与注释
- **原则**：解释“为什么”而不是“是什么”。
- **API 文档**：所有 Public 类/接口/方法必须包含文档注释（Javadoc/JSDoc/Docstring/Doxygen）。
- **版权头**：每个生成的新文件顶部必须包含以下版权声明（年份和作者根据上下文自动调整）：

```text
/*
 * Copyright 2025 [Author Name]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * [http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
````

## 5. 安全性 (Security)

  - **输入验证**：假设所有外部输入都是恶意的，必须校验类型、长度和范围。
  - **Secrets**：严禁在代码中硬编码密钥/密码，必须使用环境变量或配置服务。
  - **SQL**：必须使用参数化查询（PreparedStatement），严禁字符串拼接 SQL。

## 6. 测试 (当要求生成测试时)

  - **模式**：遵循 AAA (Arrange, Act, Assert)。
  - **隔离**：测试必须独立，使用 Mock/Stub 隔离外部依赖（DB, Network）。
  - **命名**：`testMethodName_Condition_ExpectedResult`。

## 7. Git Commit (当要求生成 Commit Msg 时)

  - **格式**：`type: short description (max 50 chars)`
  - **Type**: `feat`, `fix`, `docs`, `style`, `refactor`, `perf`, `test`, `chore`.


## 最佳实践
### Sequential thinking
使用@sequential-thinking处理复杂的编程任务、系统设计或代码生成请求。它将一个高阶问题分解为一系列可适应、可回溯、可验证的思考步骤，确保生成的代码或解决方案是**健壮、完整且可理解**的。

#### 何时使用

* 面临**复杂**、**多步骤**或**高耦合度**的编程问题。
* 需要设计一个**新的模块**、**系统架构**或**API 流程**。
* 代码生成或解决方案**缺乏清晰的分解步骤**，或者中间思路容易遗漏。
* 需要**验证**解决方案中的每一个假设和子步骤的**正确性**。

#### 核心思路与步骤

**1. 问题分解 (Breaking down complex problems into steps)**
* **编程场景应用指南**：将主要需求分解为**最小、可独立实现**的代码模块、函数或逻辑单元。例如：前端请求 -> 数据处理 -> 数据库写入。

**2. 目标与范围 (Planning and design with scope for revision)**
* **编程场景应用指南**：**定义**本次代码生成/设计要达成的**具体目标 (Goal)** 和**明确的边界 (Scope)**。任何超出边界的需求应作为未来的修订项。

**3. 识别理想解决方案 (Problem where the full scope might not be ideal/ready)**
* **编程场景应用指南**：在开始编码前，先**构想一个理想的、完整的解决方案结构 (Ideal Structure)**，即使您知道当前无法一次性实现所有细节。这有助于全局把握。

**4. 保持最小解决方案 (Decide the best to maintain the core, minimum steps)**
* **编程场景应用指南**：明确**核心功能和最小可行性产品 (MVP)** 对应的代码逻辑，确保每一步思考都围绕这个核心。

**5. 筛选相关信息 (Situation where irrelevant information needs to be filtered out)**
* **编程场景应用指南**：在提供的上下文或文档中，**过滤掉**与当前步骤无关的干扰信息，只关注与当前代码实现相关的变量、API、依赖等。

#### 思维的关键动作

在执行上述步骤时，您必须进行以下**自我检查**和**思考回溯**：

**1. 回溯与验证 (Validate & Rework)**
* 随时质疑您**上一步骤 (previous_thought)** 或 **当前假设 (hypotheses)** 的有效性。
* 验证当前代码逻辑是否**解决了**上一步分解出的子问题。
* 如果验证失败，必须**回溯 (revert)** 到上一个成功的步骤，或调整当前思路。

**2. 思考分支 (Branching Thought)**
* 如果某个子问题有**多种实现方式** (例如：递归 vs 迭代, 不同的数据结构)，将其视为一个**思考分支 (branch)**。
* 在进入分支时，**明确记录**当前状态，确保能随时返回主流程。

**3. 追踪与定量 (Tracking & Quantifying)**
* **thought_number**：为每一个核心思考步骤或代码段**编号**。
* **thought_count**：记录为解决当前问题所需的**预估思考总数**。
* **revision**：如果代码或设计被修正，**增加修订版本号**，并简要说明修订原因。

#### 参数和触发机制

以下定义了关键参数及其在编程场景中的触发条件：

* **thought**
    * **场景应用**：当前步骤代码/设计说明。
    * **触发条件**：核心输出，当生成一个**完整代码块**或**结构设计**时。

* **revision**
    * **场景应用**：代码修正次数。
    * **触发条件**：发现现有代码存在**Bug**、**性能问题**或**逻辑缺陷**，需要进行**重构**或**修正**时。

* **branchID**
    * **场景应用**：实现分支标识。
    * **触发条件**：探索**替代方案**或**不同算法**时（例如，尝试 A 方案后决定切换到 B 方案）。

* **thoughtNumber**
    * **场景应用**：当前步骤序号。
    * **触发条件**：**问题分解 (Step 1)** 后，为每一个子任务分配序号。

* **needsMoreThought**
    * **场景应用**：是否需要更多思考。
    * **触发条件**：当前代码块或设计**未完成**，或**有待优化**时（设置为 `true`）。

* **nextThoughtNeeded**
    * **场景应用**：下一个步骤说明。
    * **触发条件**：当前步骤完成后，**明确指定**下一步要实现的功能或要解决的问题。

#### 最终输出要求

您生成的最终代码或设计文档必须：

1.  **完整且可执行**：在当前定义的环境下能够运行。
2.  **可溯源**：能够通过 **thoughtNumber** 清晰地追溯其生成过程和依赖关系。
3.  **简洁一致**：针对最终答案，提供一个**单一的、高内聚的**代码或设计作为最终输出。
4.  **消除假设**：所有的中间假设或待定逻辑都已被验证或解决。

### Context7
