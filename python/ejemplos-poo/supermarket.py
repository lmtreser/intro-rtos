# Coursera - Universidad Austral
# Ejemplo de caja registradora usando Objetos
# -*- coding: utf-8 -*-
import unittest

class ProductDoesNotExist(Exception):
    pass


class ProductPriceNotDefined(Exception):
    pass


class PurchaseNotFinished(Exception):
    pass


class PurchaseAlreadyFinished(Exception):
    pass


class EmptyPurchase(Exception):
    pass

class InsufficientPayment(Exception):
    pass


class Product(object):
    
    def __init__(self, code):
        self._code = code
        
    def code(self):
        return self._code


class PriceList(object):

    def __init__(self):
        self.price_of_products = {}
        self.discount_of_products = {}

    def price_of(self, a_product):
        if not a_product in self.price_of_products.keys():
            raise ProductPriceNotDefined("El precio del producto {} no esta definido.".format(a_product.code()))
        return self.price_of_products[a_product]

    def discounted_price_of(self, a_product):
        if not a_product in self.price_of_products.keys():
            raise ProductPriceNotDefined("El precio del producto {} no esta definido.".format(a_product.code()))
        product_price = self.price_of_products[a_product]
        product_discount = self.discount_of_products.get(a_product, 0)
        return  product_price - (product_price* product_discount)


    def set_price_for(self, a_product, a_price_value):
        self.price_of_products[a_product] = a_price_value

    def set_discount_for(self, a_product, a_percentage):
        self.discount_of_products[a_product] = a_percentage


class Purchase(object):
    
    def __init__(self):
        self._products = []
        self.finished = False

    def products(self):
        return self._products

    def add_product(self, a_product):
        self._products.append(a_product)

    def finish(self):
        if self.finished:
            raise PurchaseAlreadyFinished("La compra ya se encuentra finalizada")
        if not self._products:
            raise EmptyPurchase("La compra no tiene productos")
        self.finished = True


class CashRegister(object):
    
    def __init__(self, a_product_list, a_price_list):
        self.product_list = a_product_list
        self.price_list = a_price_list
        self._current_purchase = Purchase()

    def _scan_product(self, a_product_code):
        
        selected_products = filter(lambda p: p.code() == a_product_code, self.product_list)
        if not selected_products:
            raise ProductDoesNotExist("El producto con código {} no existe".format(a_product_code))
        return selected_products[0]

    def add_product(self, a_product_code):
        a_product = self._scan_product(a_product_code)
        self.current_purchase().add_product(a_product)

    def current_purchase(self):
        return self._current_purchase

    def subtotal(self):
        subtotal = 0
        for product in self.current_purchase().products():
            subtotal += self.price_list.price_of(product)
        return subtotal

    def finish_purchase(self):
        self.current_purchase().finish()

    def total(self):
        if not self.current_purchase().finished:
            raise PurchaseNotFinished("Compra no finalizada.")
        total = 0
        for product in self.current_purchase().products():
            total += self.price_list.discounted_price_of(product)
        return total

    def pay_purchase_with(self, amount_of_money):
        total = self.total()
        if total > amount_of_money:
            raise InsufficientPayment("El pago debe ser mayor al total de la compra.")
        return amount_of_money - self.total()


class CashRegisterTest(unittest.TestCase):

    def setUp(self):
        a_product = Product('1002A')
        another_product = Product('1003A')
        product_without_price = Product('1004A')
        self.product_list = [a_product, another_product, product_without_price]

        self.price_list = PriceList()
        self.price_list.set_price_for(a_product, 10.00)
        self.price_list.set_price_for(another_product, 5.00)

        self.cash_register = CashRegister(a_product_list=self.product_list, a_price_list=self.price_list)

    def test_01_add_not_exist_product(self):
        cash_register = CashRegister(a_product_list=[], a_price_list=PriceList())
        a_product_code = '1001A'
        
        self.assertRaises(ProductDoesNotExist, cash_register.add_product, a_product_code)

    def test_02_add_exist_product(self):
        a_product_code = '1002A'
        a_product = self.cash_register.add_product(a_product_code)

        self.assertEqual(1, len(self.cash_register.current_purchase().products()))
        self.assertEqual('1002A', self.cash_register.current_purchase().products()[0].code())

    def test_03_subtotal_without_product(self):
        cash_register = CashRegister(a_product_list=[], a_price_list=PriceList())
        self.assertEqual(0, cash_register.subtotal())

    def test_04_subtotal_product_without_price(self):
        a_product_code = '1004A'
        a_product = self.cash_register.add_product(a_product_code)

        self.assertRaises(ProductPriceNotDefined, self.cash_register.subtotal)

    def test_05_subtotal_with_one_product(self):
        a_product_code = '1002A'
        a_product = self.cash_register.add_product(a_product_code)
        
        self.assertEqual(10.00, self.cash_register.subtotal())

    def test_06_subtotal_with_two_product(self):
        a_product_code = '1002A'
        self.cash_register.add_product(a_product_code)

        another_product_code = '1003A'
        self.cash_register.add_product(another_product_code)

        self.assertEqual(15.00, self.cash_register.subtotal())

    def test_07_total_without_finish_purchase(self):
        a_product_code = '1002A'
        a_product = self.cash_register.add_product(a_product_code)

        self.assertRaises(PurchaseNotFinished, self.cash_register.total)

    def test_08_finish_empty_purchase(self):
        self.assertRaises(EmptyPurchase, self.cash_register.finish_purchase)

    def test_09_finish_purchase_already_finished(self):
        a_product_code = '1002A'
        a_product = self.cash_register.add_product(a_product_code)

        self.cash_register.finish_purchase()

        self.assertRaises(PurchaseAlreadyFinished, self.cash_register.finish_purchase)

    def test_10_total_one_product_without_discount(self):
        a_product_code = '1002A'
        a_product = self.cash_register.add_product(a_product_code)

        self.cash_register.finish_purchase()

        self.assertEqual(10.00, self.cash_register.total())

    def test_11_total_two_products_without_discount(self):
        a_product_code = '1002A'
        a_product = self.cash_register.add_product(a_product_code)

        another_product_code = '1003A'
        self.cash_register.add_product(another_product_code)

        self.cash_register.finish_purchase()

        self.assertEqual(15.00, self.cash_register.total())

    def test_12_total_one_product_with_discount(self):
        a_product_code = '1002A'
        a_product = filter(lambda p: p.code() == a_product_code, self.product_list)[0]

        price_list = PriceList()
        price_list.set_price_for(a_product, 10.00)
        price_list.set_discount_for(a_product, 0.1)
        
        cash_register = CashRegister(a_product_list=self.product_list, a_price_list=price_list)
        a_product = cash_register.add_product(a_product_code)

        cash_register.finish_purchase()

        self.assertEqual(9.00, cash_register.total())

    def test_13_pay_purchase_not_enough_money(self):
        a_product_code = '1002A'
        a_product = self.cash_register.add_product(a_product_code)

        another_product_code = '1003A'
        self.cash_register.add_product(another_product_code)

        self.cash_register.finish_purchase()

        self.assertEqual(15.00, self.cash_register.total())

        self.assertRaises(InsufficientPayment, self.cash_register.pay_purchase_with, 13.00)

    def test_14_pay_purchase_without_change(self):
        a_product_code = '1002A'
        a_product = self.cash_register.add_product(a_product_code)

        another_product_code = '1003A'
        self.cash_register.add_product(another_product_code)

        self.cash_register.finish_purchase()

        self.assertEqual(15.00, self.cash_register.total())

        self.assertEqual(0.00, self.cash_register.pay_purchase_with(15.00))

    def test_15_pay_purchase_with_change(self):
        a_product_code = '1002A'
        a_product = self.cash_register.add_product(a_product_code)

        another_product_code = '1003A'
        self.cash_register.add_product(another_product_code)

        self.cash_register.finish_purchase()

        self.assertEqual(15.00, self.cash_register.total())

        self.assertEqual(5.00, self.cash_register.pay_purchase_with(20.00))


if __name__ == '__main__':
    unittest.main()