#include "pch.h"
#include "CppUnitTest.h"
#include "..\\AISD_LAB2_SEM4\HuffmanAlgorithm.h"
#include "..\\AISD_LAB2_SEM4\String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForHuffmanAlgorithm
{
	TEST_CLASS(UnitTestForHuffmanAlgorithm)
	{
	public:
		
		TEST_METHOD(CONSTRUCTOR_WITHOUT_PARAMETER)
		{
			HuffmanAlgorithm<char, int> a;
			Assert::IsTrue(a.size == 0);
		}

		TEST_METHOD(DESTRUCTOR)
		{
			HuffmanAlgorithm<char, int> a;
			a.tree_huffman_coding();
			Assert::IsTrue(a.size == 6);
			a.clear();
			Assert::IsTrue(a.size == 0);
		}

		TEST_METHOD(CODING_AND_STRING_CONVERSION)
		{
			HuffmanAlgorithm<char, int> a;
			a.tree_huffman_coding();
			//Since the input string is fed from the console, 
			//specifically for the tests, the code has changed so that the string is fixed
			// a == "it is"
			Assert::IsTrue(a.size == 6);
			Assert::IsTrue(a.root->left->left->key == 't');
			Assert::IsTrue(a.root->left->right->key == ' ');
			Assert::IsTrue(a.root->right->left->key == 's');
			Assert::IsTrue(a.root->right->right->key == 'i');
		}

		TEST_METHOD(DECODING)
		{
			HuffmanAlgorithm<char, int> a;
			a.tree_huffman_coding();
			//Since the input string is fed from the console, 
			//specifically for the tests, the code has changed so that the string is fixed
			// a == "it is"
			Assert::IsTrue(a.size == 6);
			Assert::IsTrue(a.root->left->left->key == 't');
			Assert::IsTrue(a.root->left->right->key == ' ');
			Assert::IsTrue(a.root->right->left->key == 's');
			Assert::IsTrue(a.root->right->right->key == 'i');
			
			a.tree_huffman_decoding();
			Assert::IsTrue(a.decoded_text[0] == 'i');
			Assert::IsTrue(a.decoded_text[1] == 't');
			Assert::IsTrue(a.decoded_text[2] == ' ');
			Assert::IsTrue(a.decoded_text[3] == 'i');
			Assert::IsTrue(a.decoded_text[4] == 's');
		}

		TEST_METHOD(CREATING_A_TABLE)
		{
			HuffmanAlgorithm<char, int> a;
			a.tree_huffman_coding();
			//Since the input string is fed from the console, 
			//specifically for the tests, the code has changed so that the string is fixed
			// a == "it is"
			Assert::IsTrue(a.size == 6);
			Assert::IsTrue(a.root->left->left->key == 't');
			Assert::IsTrue(a.root->left->right->key == ' ');
			Assert::IsTrue(a.root->right->left->key == 's');
			Assert::IsTrue(a.root->right->right->key == 'i');

			Assert::IsTrue(a.encoded_text[0] == '1');
			Assert::IsTrue(a.encoded_text[1] == '1');
			Assert::IsTrue(a.encoded_text[2] == '0');
			Assert::IsTrue(a.encoded_text[3] == '0');
			Assert::IsTrue(a.encoded_text[4] == '0');
			Assert::IsTrue(a.encoded_text[5] == '1');
			Assert::IsTrue(a.encoded_text[6] == '1');
			Assert::IsTrue(a.encoded_text[7] == '1');
			Assert::IsTrue(a.encoded_text[8] == '1');
			Assert::IsTrue(a.encoded_text[9] == '0');
		}
	};
}
