# sup
Automatic changelog generator for git repositories.

## Overview

Sup looks through your commit history since the last marked tag to your current head and extracts changelog data specified by `.sup` file in the repository root.

## Configuration (`.sup` file)

Line numbers are 1 indexed and parenthesis are required for regular expressions if they need to be captured. Don't forget to double escape backslashes (e.g \\d+)

```javascript
{
  "file": "CHANGELOG.md",    // Optional changelog file path relative to repository root.
                             // default "CHANGELOG.md"
                          
  "filter": "--changeLog",   // Optional regex test to decide commit should be included in changelog
                             // default ".*" (which means all commits will be included)
                            
  "tagFilter": "v*",         // Optional regex which used to find latest created tag
  
  "issueIdRegex": "#(\\d+)", // Regex capture.
                             // default "#(\\d+)" which is github issue format.
                             
  "omitNewLinesInBody": true, // Boolean. If true new lines characters will be
                             // replaced by space character in the body.
                             // default false
                             

  // change log entry template
  // available variables are $issueId, $body, $issueType
  "template": "* $body\n[$issueId](https://backbase.atlassian.net/browse/$issueId)",
  
  "issueType": { 
    // Required issue type parser options. (feature, bugfix, error, etc.)
    // There are two different methods you can use. You should choose only one
    //   1. regex - data extracted by regex capture
    //      Parenthesis are required for capturing
    //      If you specify a line number as "searchAt" it will only check the given line
    //   2. line number - data extracted as whole line
    
    "regex": "(feature|hotfix)/",
    "searchAt": 1
    // "lineNumber": 2, // don't use lineNumber with regex and searchAt
  },
  
  "body": {
    // Required changelog entry message parser options.
    // There are three different methods you can use.
    //   1. regex - data extracted by regex capture
    //      You should specify only one capture otherwise first one will be chosen
    //   2. line number - message body will be given line's content
    //   3. until given marker
    //      - you can specify starting line (default is 3)
    
    // "regex": "\[(.*)\]", // it extracts all characters between [ and ] characters
    // "lineNumber": 3,
    "startingAt": 3,
    "endOfBody": "--endOfChangelog" // it will extract lines between startingAt and the line includes marker
  }
}
```