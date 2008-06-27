/* Generated By:JavaCC: Do not edit this line. StarParserTokenManager.java */
package EDU.bmrb.starlibj;
import java.util.*;
import java.lang.*;
import java.text.*;
import EDU.bmrb.starlibj.*;

public class StarParserTokenManager implements StarParserConstants
{
    static StringBuffer skipText = null;
    static int          skipTextBeginLine = 0;
private static final int jjStopStringLiteralDfa_0(int pos, long active0)
{
   switch (pos)
   {
      default :
         return -1;
   }
}
private static final int jjStartNfa_0(int pos, long active0)
{
   return jjMoveNfa_0(jjStopStringLiteralDfa_0(pos, active0), pos + 1);
}
static private final int jjStopAtPos(int pos, int kind)
{
   jjmatchedKind = kind;
   jjmatchedPos = pos;
   return pos + 1;
}
static private final int jjStartNfaWithStates_0(int pos, int kind, int state)
{
   jjmatchedKind = kind;
   jjmatchedPos = pos;
   try { curChar = input_stream.readChar(); }
   catch(java.io.IOException e) { return pos + 1; }
   return jjMoveNfa_0(state, pos + 1);
}
static private final int jjMoveStringLiteralDfa0_0()
{
   switch(curChar)
   {
      case 10:
         return jjStartNfaWithStates_0(0, 29, 22);
      case 13:
         return jjStartNfaWithStates_0(0, 30, 33);
      case 34:
         return jjStopAtPos(0, 24);
      case 39:
         return jjStopAtPos(0, 21);
      default :
         return jjMoveNfa_0(0, 0);
   }
}
static private final void jjCheckNAdd(int state)
{
   if (jjrounds[state] != jjround)
   {
      jjstateSet[jjnewStateCnt++] = state;
      jjrounds[state] = jjround;
   }
}
static private final void jjAddStates(int start, int end)
{
   do {
      jjstateSet[jjnewStateCnt++] = jjnextStates[start];
   } while (start++ != end);
}
static private final void jjCheckNAddTwoStates(int state1, int state2)
{
   jjCheckNAdd(state1);
   jjCheckNAdd(state2);
}
static private final void jjCheckNAddStates(int start, int end)
{
   do {
      jjCheckNAdd(jjnextStates[start]);
   } while (start++ != end);
}
static private final void jjCheckNAddStates(int start)
{
   jjCheckNAdd(jjnextStates[start]);
   jjCheckNAdd(jjnextStates[start + 1]);
}
static final long[] jjbitVec0 = {
   0x0L, 0x0L, 0xffffffffffffffffL, 0xffffffffffffffffL
};
static private final int jjMoveNfa_0(int startState, int curPos)
{
   int[] nextStates;
   int startsAt = 0;
   jjnewStateCnt = 72;
   int i = 1;
   jjstateSet[0] = startState;
   int j, kind = 0x7fffffff;
   for (;;)
   {
      if (++jjround == 0x7fffffff)
         ReInitRounds();
      if (curChar < 64)
      {
         long l = 1L << curChar;
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 33:
                  if (curChar == 59)
                     jjCheckNAddStates(0, 3);
                  else if (curChar == 10)
                     jjCheckNAdd(23);
                  break;
               case 22:
                  if (curChar == 59)
                     jjCheckNAddStates(0, 3);
                  else if (curChar == 13)
                     jjCheckNAdd(23);
                  break;
               case 0:
                  if ((0xffffff7affffd9ffL & l) != 0L)
                  {
                     if (kind > 20)
                        kind = 20;
                     jjCheckNAdd(37);
                  }
                  else if ((0x2400L & l) != 0L)
                     jjCheckNAdd(23);
                  if (curChar == 35)
                  {
                     if (kind > 4)
                        kind = 4;
                     jjCheckNAddTwoStates(56, 57);
                  }
                  else if (curChar == 13)
                     jjstateSet[jjnewStateCnt++] = 33;
                  else if (curChar == 10)
                     jjstateSet[jjnewStateCnt++] = 22;
                  else if (curChar == 36)
                     jjCheckNAdd(19);
                  break;
               case 17:
                  if ((0xfffffffeffffd9ffL & l) == 0L)
                     break;
                  if (kind > 15)
                     kind = 15;
                  jjstateSet[jjnewStateCnt++] = 17;
                  break;
               case 18:
                  if (curChar == 36)
                     jjCheckNAdd(19);
                  break;
               case 19:
                  if ((0xfffffffeffffd9ffL & l) == 0L)
                     break;
                  if (kind > 17)
                     kind = 17;
                  jjCheckNAdd(19);
                  break;
               case 21:
                  if ((0xfffffffeffffd9ffL & l) == 0L)
                     break;
                  if (kind > 18)
                     kind = 18;
                  jjstateSet[jjnewStateCnt++] = 21;
                  break;
               case 23:
                  if (curChar == 59)
                     jjCheckNAddStates(0, 3);
                  break;
               case 24:
                  if ((0xf7ffffffffffdbffL & l) != 0L)
                     jjCheckNAddStates(4, 8);
                  break;
               case 25:
                  if ((0xffffffffffffdbffL & l) != 0L)
                     jjCheckNAddStates(4, 8);
                  break;
               case 26:
                  if (curChar == 13)
                     jjCheckNAddStates(9, 13);
                  break;
               case 27:
                  if (curChar == 10)
                     jjstateSet[jjnewStateCnt++] = 26;
                  break;
               case 28:
                  if (curChar == 10)
                     jjCheckNAddStates(9, 13);
                  break;
               case 29:
                  if (curChar == 13)
                     jjstateSet[jjnewStateCnt++] = 28;
                  break;
               case 30:
                  if ((0x2400L & l) != 0L)
                     jjCheckNAddStates(9, 13);
                  break;
               case 31:
                  if (curChar == 59 && kind > 19)
                     kind = 19;
                  break;
               case 32:
                  if (curChar == 10)
                     jjstateSet[jjnewStateCnt++] = 22;
                  break;
               case 34:
                  if (curChar == 13)
                     jjstateSet[jjnewStateCnt++] = 33;
                  break;
               case 35:
                  if ((0x2400L & l) != 0L)
                     jjCheckNAdd(23);
                  break;
               case 36:
                  if ((0xffffff7affffd9ffL & l) == 0L)
                     break;
                  if (kind > 20)
                     kind = 20;
                  jjCheckNAdd(37);
                  break;
               case 37:
                  if ((0xfffffffeffffd9ffL & l) == 0L)
                     break;
                  if (kind > 20)
                     kind = 20;
                  jjCheckNAdd(37);
                  break;
               case 38:
                  if (curChar != 35)
                     break;
                  if (kind > 4)
                     kind = 4;
                  jjCheckNAddTwoStates(56, 57);
                  break;
               case 39:
                  if (curChar == 62)
                     jjCheckNAddStates(14, 17);
                  break;
               case 40:
                  if ((0x100000200L & l) != 0L)
                     jjCheckNAddStates(14, 17);
                  break;
               case 41:
                  if (curChar == 13 && kind > 1)
                     kind = 1;
                  break;
               case 42:
                  if (curChar == 10)
                     jjstateSet[jjnewStateCnt++] = 41;
                  break;
               case 43:
                  if (curChar == 10 && kind > 1)
                     kind = 1;
                  break;
               case 44:
                  if (curChar == 13)
                     jjstateSet[jjnewStateCnt++] = 43;
                  break;
               case 45:
                  if ((0x2400L & l) != 0L && kind > 1)
                     kind = 1;
                  break;
               case 50:
                  if (curChar == 45)
                     jjstateSet[jjnewStateCnt++] = 49;
                  break;
               case 56:
                  if (curChar == 60)
                     jjstateSet[jjnewStateCnt++] = 55;
                  break;
               case 57:
                  if ((0xffffffffffffdbffL & l) == 0L)
                     break;
                  if (kind > 4)
                     kind = 4;
                  jjCheckNAdd(57);
                  break;
               case 71:
                  if ((0xfffffffeffffd9ffL & l) == 0L)
                     break;
                  if (kind > 16)
                     kind = 16;
                  jjstateSet[jjnewStateCnt++] = 71;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else if (curChar < 128)
      {
         long l = 1L << (curChar & 077);
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
                  if ((0xffffffff7fffffffL & l) != 0L)
                  {
                     if (kind > 20)
                        kind = 20;
                     jjCheckNAdd(37);
                  }
                  else if (curChar == 95)
                     jjCheckNAdd(21);
                  if ((0x8000000080000L & l) != 0L)
                     jjAddStates(18, 20);
                  else if ((0x1000000010L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 13;
                  else if ((0x8000000080L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 6;
                  else if ((0x100000001000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 1;
                  break;
               case 1:
                  if ((0x800000008000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 2;
                  break;
               case 2:
                  if ((0x800000008000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 3;
                  break;
               case 3:
                  if ((0x1000000010000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 4;
                  break;
               case 4:
                  if (curChar == 95 && kind > 11)
                     kind = 11;
                  break;
               case 5:
                  if ((0x8000000080L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 6;
                  break;
               case 6:
                  if ((0x100000001000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 7;
                  break;
               case 7:
                  if ((0x800000008000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 8;
                  break;
               case 8:
                  if ((0x400000004L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 9;
                  break;
               case 9:
                  if ((0x200000002L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 10;
                  break;
               case 10:
                  if ((0x100000001000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 11;
                  break;
               case 11:
                  if (curChar == 95 && kind > 12)
                     kind = 12;
                  break;
               case 12:
                  if ((0x1000000010L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 13;
                  break;
               case 13:
                  if ((0x200000002L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 14;
                  break;
               case 14:
                  if ((0x10000000100000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 15;
                  break;
               case 15:
                  if ((0x200000002L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 16;
                  break;
               case 16:
                  if (curChar == 95)
                     jjCheckNAdd(17);
                  break;
               case 17:
                  if (kind > 15)
                     kind = 15;
                  jjCheckNAdd(17);
                  break;
               case 19:
                  if (kind > 17)
                     kind = 17;
                  jjstateSet[jjnewStateCnt++] = 19;
                  break;
               case 20:
                  if (curChar == 95)
                     jjCheckNAdd(21);
                  break;
               case 21:
                  if (kind > 18)
                     kind = 18;
                  jjCheckNAdd(21);
                  break;
               case 24:
               case 25:
                  jjCheckNAddStates(4, 8);
                  break;
               case 36:
                  if ((0xffffffff7fffffffL & l) == 0L)
                     break;
                  if (kind > 20)
                     kind = 20;
                  jjCheckNAdd(37);
                  break;
               case 37:
                  if (kind > 20)
                     kind = 20;
                  jjCheckNAdd(37);
                  break;
               case 46:
                  if (curChar == 80)
                     jjstateSet[jjnewStateCnt++] = 39;
                  break;
               case 47:
                  if (curChar == 73)
                     jjstateSet[jjnewStateCnt++] = 46;
                  break;
               case 48:
                  if (curChar == 75)
                     jjstateSet[jjnewStateCnt++] = 47;
                  break;
               case 49:
                  if (curChar == 83)
                     jjstateSet[jjnewStateCnt++] = 48;
                  break;
               case 51:
                  if (curChar == 84)
                     jjstateSet[jjnewStateCnt++] = 50;
                  break;
               case 52:
                  if (curChar == 82)
                     jjstateSet[jjnewStateCnt++] = 51;
                  break;
               case 53:
                  if (curChar == 65)
                     jjstateSet[jjnewStateCnt++] = 52;
                  break;
               case 54:
                  if (curChar == 84)
                     jjstateSet[jjnewStateCnt++] = 53;
                  break;
               case 55:
                  if (curChar == 83)
                     jjstateSet[jjnewStateCnt++] = 54;
                  break;
               case 57:
                  if (kind > 4)
                     kind = 4;
                  jjstateSet[jjnewStateCnt++] = 57;
                  break;
               case 58:
                  if ((0x8000000080000L & l) != 0L)
                     jjAddStates(18, 20);
                  break;
               case 59:
                  if ((0x10000000100000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 60;
                  break;
               case 60:
                  if ((0x800000008000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 61;
                  break;
               case 61:
                  if ((0x1000000010000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 62;
                  break;
               case 62:
                  if (curChar == 95 && kind > 13)
                     kind = 13;
                  break;
               case 63:
                  if ((0x200000002L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 64;
                  break;
               case 64:
                  if ((0x40000000400000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 65;
                  break;
               case 65:
                  if ((0x2000000020L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 66;
                  break;
               case 66:
                  if (curChar == 95 && kind > 14)
                     kind = 14;
                  break;
               case 67:
                  if ((0x200000002L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 68;
                  break;
               case 68:
                  if ((0x40000000400000L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 69;
                  break;
               case 69:
                  if ((0x2000000020L & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 70;
                  break;
               case 70:
                  if (curChar == 95)
                     jjCheckNAdd(71);
                  break;
               case 71:
                  if (kind > 16)
                     kind = 16;
                  jjCheckNAdd(71);
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else
      {
         int i2 = (curChar & 0xff) >> 6;
         long l2 = 1L << (curChar & 077);
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
               case 37:
                  if ((jjbitVec0[i2] & l2) == 0L)
                     break;
                  if (kind > 20)
                     kind = 20;
                  jjCheckNAdd(37);
                  break;
               case 17:
                  if ((jjbitVec0[i2] & l2) == 0L)
                     break;
                  if (kind > 15)
                     kind = 15;
                  jjstateSet[jjnewStateCnt++] = 17;
                  break;
               case 19:
                  if ((jjbitVec0[i2] & l2) == 0L)
                     break;
                  if (kind > 17)
                     kind = 17;
                  jjstateSet[jjnewStateCnt++] = 19;
                  break;
               case 21:
                  if ((jjbitVec0[i2] & l2) == 0L)
                     break;
                  if (kind > 18)
                     kind = 18;
                  jjstateSet[jjnewStateCnt++] = 21;
                  break;
               case 24:
               case 25:
                  if ((jjbitVec0[i2] & l2) != 0L)
                     jjCheckNAddStates(4, 8);
                  break;
               case 57:
                  if ((jjbitVec0[i2] & l2) == 0L)
                     break;
                  if (kind > 4)
                     kind = 4;
                  jjstateSet[jjnewStateCnt++] = 57;
                  break;
               case 71:
                  if ((jjbitVec0[i2] & l2) == 0L)
                     break;
                  if (kind > 16)
                     kind = 16;
                  jjstateSet[jjnewStateCnt++] = 71;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      if (kind != 0x7fffffff)
      {
         jjmatchedKind = kind;
         jjmatchedPos = curPos;
         kind = 0x7fffffff;
      }
      ++curPos;
      if ((i = jjnewStateCnt) == (startsAt = 72 - (jjnewStateCnt = startsAt)))
         return curPos;
      try { curChar = input_stream.readChar(); }
      catch(java.io.IOException e) { return curPos; }
   }
}
static private final int jjMoveStringLiteralDfa0_2()
{
   return jjMoveNfa_2(0, 0);
}
static private final int jjMoveNfa_2(int startState, int curPos)
{
   int[] nextStates;
   int startsAt = 0;
   jjnewStateCnt = 3;
   int i = 1;
   jjstateSet[0] = startState;
   int j, kind = 0x7fffffff;
   for (;;)
   {
      if (++jjround == 0x7fffffff)
         ReInitRounds();
      if (curChar < 64)
      {
         long l = 1L << curChar;
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
                  if ((0xffffffffffffdbffL & l) != 0L)
                  {
                     if (kind > 23)
                        kind = 23;
                  }
                  if (curChar == 39)
                     jjstateSet[jjnewStateCnt++] = 1;
                  break;
               case 1:
                  if ((0x100002600L & l) != 0L && kind > 22)
                     kind = 22;
                  break;
               case 2:
                  if ((0xffffffffffffdbffL & l) != 0L && kind > 23)
                     kind = 23;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else if (curChar < 128)
      {
         long l = 1L << (curChar & 077);
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
                  kind = 23;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else
      {
         int i2 = (curChar & 0xff) >> 6;
         long l2 = 1L << (curChar & 077);
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
                  if ((jjbitVec0[i2] & l2) != 0L && kind > 23)
                     kind = 23;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      if (kind != 0x7fffffff)
      {
         jjmatchedKind = kind;
         jjmatchedPos = curPos;
         kind = 0x7fffffff;
      }
      ++curPos;
      if ((i = jjnewStateCnt) == (startsAt = 3 - (jjnewStateCnt = startsAt)))
         return curPos;
      try { curChar = input_stream.readChar(); }
      catch(java.io.IOException e) { return curPos; }
   }
}
static private final int jjMoveStringLiteralDfa0_3()
{
   return jjMoveNfa_3(0, 0);
}
static private final int jjMoveNfa_3(int startState, int curPos)
{
   int[] nextStates;
   int startsAt = 0;
   jjnewStateCnt = 3;
   int i = 1;
   jjstateSet[0] = startState;
   int j, kind = 0x7fffffff;
   for (;;)
   {
      if (++jjround == 0x7fffffff)
         ReInitRounds();
      if (curChar < 64)
      {
         long l = 1L << curChar;
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
                  if ((0xffffffffffffdbffL & l) != 0L)
                  {
                     if (kind > 26)
                        kind = 26;
                  }
                  if (curChar == 34)
                     jjstateSet[jjnewStateCnt++] = 1;
                  break;
               case 1:
                  if ((0x100002600L & l) != 0L && kind > 25)
                     kind = 25;
                  break;
               case 2:
                  if ((0xffffffffffffdbffL & l) != 0L && kind > 26)
                     kind = 26;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else if (curChar < 128)
      {
         long l = 1L << (curChar & 077);
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
                  kind = 26;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else
      {
         int i2 = (curChar & 0xff) >> 6;
         long l2 = 1L << (curChar & 077);
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
                  if ((jjbitVec0[i2] & l2) != 0L && kind > 26)
                     kind = 26;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      if (kind != 0x7fffffff)
      {
         jjmatchedKind = kind;
         jjmatchedPos = curPos;
         kind = 0x7fffffff;
      }
      ++curPos;
      if ((i = jjnewStateCnt) == (startsAt = 3 - (jjnewStateCnt = startsAt)))
         return curPos;
      try { curChar = input_stream.readChar(); }
      catch(java.io.IOException e) { return curPos; }
   }
}
static private final int jjMoveStringLiteralDfa0_1()
{
   return jjMoveNfa_1(0, 0);
}
static private final int jjMoveNfa_1(int startState, int curPos)
{
   int[] nextStates;
   int startsAt = 0;
   jjnewStateCnt = 23;
   int i = 1;
   jjstateSet[0] = startState;
   int j, kind = 0x7fffffff;
   for (;;)
   {
      if (++jjround == 0x7fffffff)
         ReInitRounds();
      if (curChar < 64)
      {
         long l = 1L << curChar;
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
                  if ((0xffffffffffffdbffL & l) != 0L)
                     jjCheckNAddStates(21, 24);
                  else if ((0x2400L & l) != 0L)
                  {
                     if (kind > 3)
                        kind = 3;
                  }
                  if (curChar == 13)
                     jjstateSet[jjnewStateCnt++] = 20;
                  else if (curChar == 10)
                     jjstateSet[jjnewStateCnt++] = 18;
                  else if (curChar == 35)
                     jjstateSet[jjnewStateCnt++] = 16;
                  break;
               case 1:
                  if (curChar == 62)
                     jjCheckNAddStates(25, 28);
                  break;
               case 2:
                  if ((0x100000200L & l) != 0L)
                     jjCheckNAddStates(25, 28);
                  break;
               case 3:
                  if (curChar == 13 && kind > 2)
                     kind = 2;
                  break;
               case 4:
                  if (curChar == 10)
                     jjstateSet[jjnewStateCnt++] = 3;
                  break;
               case 5:
                  if (curChar == 10 && kind > 2)
                     kind = 2;
                  break;
               case 6:
                  if (curChar == 13)
                     jjstateSet[jjnewStateCnt++] = 5;
                  break;
               case 7:
                  if ((0x2400L & l) != 0L && kind > 2)
                     kind = 2;
                  break;
               case 12:
                  if (curChar == 45)
                     jjstateSet[jjnewStateCnt++] = 11;
                  break;
               case 16:
                  if (curChar == 60)
                     jjstateSet[jjnewStateCnt++] = 15;
                  break;
               case 17:
                  if ((0xffffffffffffdbffL & l) != 0L)
                     jjCheckNAddStates(21, 24);
                  break;
               case 18:
                  if (curChar == 13 && kind > 3)
                     kind = 3;
                  break;
               case 19:
                  if (curChar == 10)
                     jjstateSet[jjnewStateCnt++] = 18;
                  break;
               case 20:
                  if (curChar == 10 && kind > 3)
                     kind = 3;
                  break;
               case 21:
                  if (curChar == 13)
                     jjstateSet[jjnewStateCnt++] = 20;
                  break;
               case 22:
                  if ((0x2400L & l) != 0L && kind > 3)
                     kind = 3;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else if (curChar < 128)
      {
         long l = 1L << (curChar & 077);
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
               case 17:
                  jjCheckNAddStates(21, 24);
                  break;
               case 8:
                  if (curChar == 80)
                     jjstateSet[jjnewStateCnt++] = 1;
                  break;
               case 9:
                  if (curChar == 73)
                     jjstateSet[jjnewStateCnt++] = 8;
                  break;
               case 10:
                  if (curChar == 75)
                     jjstateSet[jjnewStateCnt++] = 9;
                  break;
               case 11:
                  if (curChar == 83)
                     jjstateSet[jjnewStateCnt++] = 10;
                  break;
               case 13:
                  if (curChar == 68)
                     jjstateSet[jjnewStateCnt++] = 12;
                  break;
               case 14:
                  if (curChar == 78)
                     jjstateSet[jjnewStateCnt++] = 13;
                  break;
               case 15:
                  if (curChar == 69)
                     jjstateSet[jjnewStateCnt++] = 14;
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else
      {
         int i2 = (curChar & 0xff) >> 6;
         long l2 = 1L << (curChar & 077);
         MatchLoop: do
         {
            switch(jjstateSet[--i])
            {
               case 0:
               case 17:
                  if ((jjbitVec0[i2] & l2) != 0L)
                     jjCheckNAddStates(21, 24);
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      if (kind != 0x7fffffff)
      {
         jjmatchedKind = kind;
         jjmatchedPos = curPos;
         kind = 0x7fffffff;
      }
      ++curPos;
      if ((i = jjnewStateCnt) == (startsAt = 23 - (jjnewStateCnt = startsAt)))
         return curPos;
      try { curChar = input_stream.readChar(); }
      catch(java.io.IOException e) { return curPos; }
   }
}
static final int[] jjnextStates = {
   24, 27, 29, 30, 24, 25, 27, 29, 30, 24, 27, 29, 30, 31, 40, 42, 
   44, 45, 59, 63, 67, 17, 19, 21, 22, 2, 4, 6, 7, 
};
public static final String[] jjstrLiteralImages = {
"", null, null, null, null, null, null, null, null, null, null, null, null, 
null, null, null, null, null, null, null, null, null, null, null, null, null, null, 
null, null, null, null, };
public static final String[] lexStateNames = {
   "DEFAULT", 
   "SKIPTEXT_STATE", 
   "SQUOTESTATE", 
   "DQUOTESTATE", 
};
public static final int[] jjnewLexState = {
   -1, 1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, 0, -1, 3, 
   0, -1, -1, -1, -1, -1, 
};
static final long[] jjtoToken = {
   0x25ff801L, 
};
static final long[] jjtoSkip = {
   0x7800001eL, 
};
static final long[] jjtoSpecial = {
   0x1eL, 
};
static final long[] jjtoMore = {
   0x5a00000L, 
};
static private ASCII_CharStream input_stream;
static private final int[] jjrounds = new int[72];
static private final int[] jjstateSet = new int[144];
static StringBuffer image;
static int jjimageLen;
static int lengthOfMatch;
static protected char curChar;
public StarParserTokenManager(ASCII_CharStream stream)
{
   if (input_stream != null)
      throw new TokenMgrError("ERROR: Second call to constructor of static lexer. You must use ReInit() to initialize the static variables.", TokenMgrError.STATIC_LEXER_ERROR);
   input_stream = stream;
}
public StarParserTokenManager(ASCII_CharStream stream, int lexState)
{
   this(stream);
   SwitchTo(lexState);
}
static public void ReInit(ASCII_CharStream stream)
{
   jjmatchedPos = jjnewStateCnt = 0;
   curLexState = defaultLexState;
   input_stream = stream;
   ReInitRounds();
}
static private final void ReInitRounds()
{
   int i;
   jjround = 0x80000001;
   for (i = 72; i-- > 0;)
      jjrounds[i] = 0x80000000;
}
static public void ReInit(ASCII_CharStream stream, int lexState)
{
   ReInit(stream);
   SwitchTo(lexState);
}
static public void SwitchTo(int lexState)
{
   if (lexState >= 4 || lexState < 0)
      throw new TokenMgrError("Error: Ignoring invalid lexical state : " + lexState + ". State unchanged.", TokenMgrError.INVALID_LEXICAL_STATE);
   else
      curLexState = lexState;
}

static private final Token jjFillToken()
{
   Token t = Token.newToken(jjmatchedKind);
   t.kind = jjmatchedKind;
   String im = jjstrLiteralImages[jjmatchedKind];
   t.image = (im == null) ? input_stream.GetImage() : im;
   t.beginLine = input_stream.getBeginLine();
   t.beginColumn = input_stream.getBeginColumn();
   t.endLine = input_stream.getEndLine();
   t.endColumn = input_stream.getEndColumn();
   return t;
}

static int curLexState = 0;
static int defaultLexState = 0;
static int jjnewStateCnt;
static int jjround;
static int jjmatchedPos;
static int jjmatchedKind;

public static final Token getNextToken() 
{
  int kind;
  Token specialToken = null;
  Token matchedToken;
  int curPos = 0;

  EOFLoop :
  for (;;)
  {   
   try   
   {     
      curChar = input_stream.BeginToken();
   }     
   catch(java.io.IOException e)
   {        
      jjmatchedKind = 0;
      matchedToken = jjFillToken();
      matchedToken.specialToken = specialToken;
      return matchedToken;
   }
   image = null;
   jjimageLen = 0;

   for (;;)
   {
     switch(curLexState)
     {
       case 0:
         try { input_stream.backup(0);
            while (curChar <= 32 && (0x100000200L & (1L << curChar)) != 0L)
               curChar = input_stream.BeginToken();
         }
         catch (java.io.IOException e1) { continue EOFLoop; }
         jjmatchedKind = 0x7fffffff;
         jjmatchedPos = 0;
         curPos = jjMoveStringLiteralDfa0_0();
         break;
       case 1:
         jjmatchedKind = 0x7fffffff;
         jjmatchedPos = 0;
         curPos = jjMoveStringLiteralDfa0_1();
         break;
       case 2:
         jjmatchedKind = 0x7fffffff;
         jjmatchedPos = 0;
         curPos = jjMoveStringLiteralDfa0_2();
         break;
       case 3:
         jjmatchedKind = 0x7fffffff;
         jjmatchedPos = 0;
         curPos = jjMoveStringLiteralDfa0_3();
         break;
     }
     if (jjmatchedKind != 0x7fffffff)
     {
        if (jjmatchedPos + 1 < curPos)
           input_stream.backup(curPos - jjmatchedPos - 1);
        if ((jjtoToken[jjmatchedKind >> 6] & (1L << (jjmatchedKind & 077))) != 0L)
        {
           matchedToken = jjFillToken();
           matchedToken.specialToken = specialToken;
           TokenLexicalActions(matchedToken);
       if (jjnewLexState[jjmatchedKind] != -1)
         curLexState = jjnewLexState[jjmatchedKind];
           return matchedToken;
        }
        else if ((jjtoSkip[jjmatchedKind >> 6] & (1L << (jjmatchedKind & 077))) != 0L)
        {
           if ((jjtoSpecial[jjmatchedKind >> 6] & (1L << (jjmatchedKind & 077))) != 0L)
           {
              matchedToken = jjFillToken();
              if (specialToken == null)
                 specialToken = matchedToken;
              else
              {
                 matchedToken.specialToken = specialToken;
                 specialToken = (specialToken.next = matchedToken);
              }
              SkipLexicalActions(matchedToken);
           }
           else 
              SkipLexicalActions(null);
         if (jjnewLexState[jjmatchedKind] != -1)
           curLexState = jjnewLexState[jjmatchedKind];
           continue EOFLoop;
        }
        jjimageLen += jjmatchedPos + 1;
      if (jjnewLexState[jjmatchedKind] != -1)
        curLexState = jjnewLexState[jjmatchedKind];
        curPos = 0;
        jjmatchedKind = 0x7fffffff;
        try {
           curChar = input_stream.readChar();
           continue;
        }
        catch (java.io.IOException e1) { }
     }
     int error_line = input_stream.getEndLine();
     int error_column = input_stream.getEndColumn();
     String error_after = null;
     boolean EOFSeen = false;
     try { input_stream.readChar(); input_stream.backup(1); }
     catch (java.io.IOException e1) {
        EOFSeen = true;
        error_after = curPos <= 1 ? "" : input_stream.GetImage();
        if (curChar == '\n' || curChar == '\r') {
           error_line++;
           error_column = 0;
        }
        else
           error_column++;
     }
     if (!EOFSeen) {
        input_stream.backup(1);
        error_after = curPos <= 1 ? "" : input_stream.GetImage();
     }
     throw new TokenMgrError(EOFSeen, curLexState, error_line, error_column, error_after, curChar, TokenMgrError.LEXICAL_ERROR);
   }
  }
}

static final void SkipLexicalActions(Token matchedToken)
{
   switch(jjmatchedKind)
   {
      case 1 :
         if (image == null)
            image = new StringBuffer(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
         else
            image.append(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
        if( skipText == null )
            skipText = new StringBuffer();
        skipText.delete( 0, skipText.length() );
        skipText.append( image );
        skipTextBeginLine = matchedToken.beginLine;
        matchedToken.image = "";
         break;
      case 2 :
         if (image == null)
            image = new StringBuffer(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
         else
            image.append(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
        skipText.append( image );
        StarParser.saveSkippedString(skipTextBeginLine, skipText );
        skipText.delete( 0, skipText.length() );
        matchedToken.image = "";
         break;
      case 3 :
         if (image == null)
            image = new StringBuffer(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
         else
            image.append(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
       skipText.append(image);
       matchedToken.image = "";
         break;
      default :
         break;
   }
}
static final void TokenLexicalActions(Token matchedToken)
{
   switch(jjmatchedKind)
   {
      case 22 :
        if (image == null)
            image = new StringBuffer(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
         else
            image.append(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
            input_stream.backup(1);
         break;
      case 25 :
        if (image == null)
            image = new StringBuffer(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
         else
            image.append(new String(input_stream.GetSuffix(jjimageLen + (lengthOfMatch = jjmatchedPos + 1))));
            input_stream.backup(1);
         break;
      default : 
         break;
   }
}
}