/***********************************************************************
 * Header:
 *    BINARY NODE
 * Summary:
 *    One node in a binary tree (and the functions to support them).
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        BNode         : A class representing a BNode
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <iostream>  // for OFSTREAM
#include <cassert>

/*****************************************************************
 * BNODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BNode
{
public:
   // 
   // Construct
   //
   BNode(): pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(0)                  { }
   
   BNode(const T& t) : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(t)       { }

   BNode(T&& t) : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(std::move(t)) { }

   //
   // Data
   //
   BNode <T>* pLeft;
   BNode <T>* pRight;
   BNode <T>* pParent;
   T data;
};

/*******************************************************************
 * SIZE BTREE
 * Return the size of a b-tree under the current node
 *******************************************************************/
template <class T>
inline size_t size(const BNode <T> * p)
{
   if (p == nullptr)
      return 0;
   
   else
      return size(p->pLeft) + 1 + size(p->pRight);
}


/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft(BNode <T> * pNode, BNode <T> * pAdd)
{
   if (pAdd != nullptr)
      pAdd->pParent = pNode;
   
   pNode->pLeft = pAdd;
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
inline void addRight (BNode <T> * pNode, BNode <T> * pAdd)
{
   if (pAdd != nullptr)
      pAdd->pParent = pNode;
   
   pNode->pRight = pAdd;
}

/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft (BNode <T> * pNode, const T & t)
{

   auto pAdd = new BNode <T>(t);
   pAdd->pParent = pNode;
   pNode->pLeft = pAdd;
}

template <class T>
inline void addLeft(BNode <T>* pNode, T && t)
{
   auto pAdd = new BNode <T>(t);
   pAdd->pParent = pNode;
   pNode->pLeft = pAdd;
   
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
void addRight (BNode <T> * pNode, const T & t)
{
   auto pAdd = new BNode <T>(t);
   pAdd->pParent = pNode;
   pNode->pRight = pAdd;
}

template <class T>
void addRight(BNode <T>* pNode, T && t)
{
   auto pAdd = new BNode <T>(t);
   pAdd->pParent = pNode;
   pNode->pRight = pAdd;
}

/*****************************************************
 * DELETE BINARY TREE
 * Delete all the nodes below pThis including pThis
 * using postfix traverse: LRV
 ****************************************************/
template <class T>
void clear(BNode <T> * & pThis)
{
   if (pThis == nullptr)
      return;
   
   clear(pThis->pLeft);
   clear(pThis->pRight);
   delete pThis;
   pThis = nullptr;
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(BNode <T>*& pLHS, BNode <T>*& pRHS) { std::swap(pLHS, pRHS); }

/**********************************************
 * COPY BINARY TREE
 * Copy pSrc->pRight to pDest->pRight and
 * pSrc->pLeft onto pDest->pLeft
 *********************************************/
template <class T>
BNode <T> * copy(const BNode <T> * pSrc)
{
   // Copy if pSource is not null
   if(pSrc == nullptr)
      return nullptr;
   auto destination = new BNode <T>(pSrc->data);
   destination->pLeft = copy(pSrc->pLeft);
   
   if (destination->pLeft != nullptr)
   {
      destination->pLeft->pParent = destination;
   }
   
   destination->pRight = copy(pSrc->pRight);
   
   if (destination->pRight != nullptr)
   {
      destination->pRight->pParent = destination;
   }

   return destination;
}

/**********************************************
 * assign
 * copy the values from pSrc onto pDest preserving
 * as many of the nodes as possible.
 *********************************************/
template <class T>
void assign(BNode <T> * & pDest, const BNode <T>* pSrc)
{
   if (pSrc == nullptr)
   {
      clear(pDest);
      return;
   }
   
   if (pDest == nullptr && pSrc != nullptr)
   {
      
      pDest = new BNode <T>(pSrc->data);
      assign(pDest->pRight, pSrc->pRight);
      assign(pDest->pLeft, pSrc->pLeft);
   }
   if (pDest != nullptr && pSrc != nullptr)
   {
      pDest->data = pSrc->data;
      assign(pDest->pRight, pSrc->pRight);
      assign(pDest->pLeft, pSrc->pLeft);
   }
}
