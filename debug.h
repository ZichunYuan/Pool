/* this file is mandatory so we can run 3 ways:
 * GRAPHICS  set to 1 - supresses ALL text output, draws instead.
 * GRAPHICS  set to 0 - text mode, VERBOSE controls what prints.
 * TEXT has 2 modes:
 * VERBOSE to 1 to get DEBUG output
 * VERBOSE to 0 to get only the required text output
 * Do not set Text or DEBUG directly; change GRAPHICS and VERBOSE instead.
 */


#define VERBOSE 0	/*: ALL MESSAGES, 0: ONLY REQUIRED MESSAGES */
#define TEXT (! GRAPHICS)
#define GRAPHICS 1	/* 1 for graphics and no text, 0 for text only */

#define DEBUG (VERBOSE && TEXT)
